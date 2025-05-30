#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Mi 10";
const char* password = "77777777";

// MQTT Broker IP & credentials
const char* mqtt_server = "206.189.51.153";
const char* mqtt_user = "userA";
const char* mqtt_password = "12345678913";

// Pin definitions
const int relayPin = 22;
const int ldrPin = 35;
const int pirPin = 14;
const int micPin = 34;

WiFiClient espClient;
PubSubClient client(espClient);

// States
bool relayOn = false;
int lastPirState = LOW;

// Clap detection
const int clapThreshold = 500;
const int clapDebounce = 200;
const int doubleClapWindow = 500;
unsigned long lastClapTime = 0;
unsigned long firstClapTime = 0;
int clapCount = 0;

void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  if (String(topic) == "home/relay1/control") {
    if (message == "ON") {
      relayOn = true;
      digitalWrite(relayPin, HIGH);
    } else if (message == "OFF") {
      relayOn = false;
      digitalWrite(relayPin, LOW);
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.subscribe("home/relay1/control");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  pinMode(ldrPin, INPUT);
  pinMode(pirPin, INPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Publish LDR value
  int ldrValue = analogRead(ldrPin);
  char ldrStr[10];
  sprintf(ldrStr, "%d", ldrValue);
  client.publish("home/relay1/photoresistor", ldrStr);

  // Publish PIR changes
  int pirState = digitalRead(pirPin);
 // if (pirState != lastPirState) {
    client.publish("home/relay1/pir", pirState == HIGH ? "Motion2" : "No motion2");
    Serial.println(pirState == HIGH ? "Motion2" : "No motion2" );
   // lastPirState = pirState;
 // }

  // Detect double clap
  int micValue = analogRead(micPin);
  unsigned long currentTime = millis();
  Serial.println(micValue);
  if (micValue > clapThreshold && (currentTime - lastClapTime) > clapDebounce) {
    lastClapTime = currentTime;
    clapCount++;
    if (clapCount == 1) {
      firstClapTime = currentTime;
    //  Serial.println("First clap detected!");
    } else if (clapCount == 2 && (currentTime - firstClapTime) <= doubleClapWindow) {
      Serial.println("Double clap detected! Toggling relay.");
      relayOn = !relayOn;
      digitalWrite(relayPin, relayOn ? HIGH : LOW);
      clapCount = 0;
    } else if ((currentTime - firstClapTime) > doubleClapWindow) {
      clapCount = 0;
    }
  }

  delay(1000);
}
