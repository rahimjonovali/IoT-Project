// #include <WiFi.h>
// #include <HTTPClient.h>
// #include <Arduino_JSON.h>

// // Replace with your actual WiFi credentials
// const char* ssid = "Mi 10";
// const char* password = "22222222";

// // Replace with your OpenWeatherMap API key
// String openWeatherMapApiKey = "42342f9399873f9fc8c61865fec9fb46";

// // City and Country Code
// String city = "Tashkent";
// String countryCode = "UZ";

// // Timing
// unsigned long lastTime = 0;
// unsigned long timerDelay = 10000; // 10 seconds

// String jsonBuffer;

// // ========= HTTP GET Request Function =========
// String httpGETRequest(const char* serverName) {
//   WiFiClient client;
//   HTTPClient http;

//   http.begin(client, serverName);
//   int httpResponseCode = http.GET();

//   String payload = "{}";

//   if (httpResponseCode > 0) {
//     Serial.print("HTTP Response code: ");
//     Serial.println(httpResponseCode);
//     payload = http.getString();
//   } else {
//     Serial.print("Error code: ");
//     Serial.println(httpResponseCode);
//   }

//   http.end();
//   return payload;
// }

// // ========= Setup =========
// void setup() {
//   Serial.begin(115200);

//   WiFi.begin(ssid, password);
//   Serial.println("Connecting to WiFi...");
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println();
//   Serial.print("Connected! IP: ");
//   Serial.println(WiFi.localIP());

//   Serial.println("Waiting 10 seconds before first request...");
// }

// // ========= Loop =========
// void loop() {
//   if ((millis() - lastTime) > timerDelay) {
//     if (WiFi.status() == WL_CONNECTED) {
//       String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&units=metric&APPID=" + openWeatherMapApiKey;

//       jsonBuffer = httpGETRequest(serverPath.c_str());
//       Serial.println("Raw JSON:");
//       Serial.println(jsonBuffer);

//       JSONVar myObject = JSON.parse(jsonBuffer);

//       if (JSON.typeof(myObject) == "undefined") {
//         Serial.println("❌ Failed to parse JSON.");
//         return;
//       }

//       Serial.println("✅ Weather Data:");
//       Serial.print("City: ");
//       Serial.println((const char*)myObject["name"]);

//       Serial.print("Temperature (°C): ");
//       Serial.println((double)myObject["main"]["temp"]);

//       Serial.print("Pressure (hPa): ");
//       Serial.println((int)myObject["main"]["pressure"]);

//       Serial.print("Humidity (%): ");
//       Serial.println((int)myObject["main"]["humidity"]);

//       Serial.print("Wind Speed (m/s): ");
//       Serial.println((double)myObject["wind"]["speed"]);
//     } else {
//       Serial.println("❌ WiFi Disconnected.");
//     }
//     lastTime = millis();
//   }
// }
