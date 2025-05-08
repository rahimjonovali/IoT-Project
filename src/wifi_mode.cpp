// #include <Arduino.h>
// #include <WiFi.h>
// #define LED 2

// const char* ssid = "Ikrom_180";
// const char* password = "123456789";

// void initWiFi() {
//   WiFi.mode(WIFI_STA);
//   WiFi.begin(ssid, password);
//   Serial.print("Connecting to My WiFi called Mi 10 ..");
//   while (WiFi.status() != WL_CONNECTED) {
//     Serial.print('.');
//     delay(1000);
//   }
//   Serial.println(WiFi.localIP());
// }


// void setup() {
//   Serial.begin(115200);
//   initWiFi();
//   Serial.print("RRSI: ");
//   Serial.println(WiFi.RSSI());
// }

// void loop() {
//     if (WiFi.status() == WL_CONNECTED) {
//     Serial.println("WiFi is connected.");
//   } else {
//     Serial.println("WiFi is NOT connected.");
//   }
//   Serial.println(WiFi.localIP() + "SSSSSSSSS");
//   delay(5000);
// }