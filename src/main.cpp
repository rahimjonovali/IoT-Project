#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "Mi 10";
const char* password = "77777777";

// MQTT Broker IP
const char* mqtt_server = "206.189.51.153";
const char* mqtt_user = "userA";
const char* mqtt_password = "12345678913";

// WiFi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);

// Relay pin
const int relayPin = 2;
// const int ledPin = 2;
void setup_wifi() {
  delay(10);
  Serial.println("Connecting to My WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  if (message == "ON") {
    digitalWrite(relayPin, HIGH);
  } else if (message == "OFF") {
    digitalWrite(relayPin, LOW);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client", mqtt_user,mqtt_password)) {
      Serial.println("\nConnected to");
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
  digitalWrite(relayPin, LOW);  // Start with relay OFF

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
