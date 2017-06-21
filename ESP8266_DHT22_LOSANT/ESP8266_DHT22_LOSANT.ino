
#include <DHT.h>
#include <DHT_U.h>
#include <ESP8266WiFi.h>
#include <Losant.h>
// WiFi credentials.
const char* WIFI_SSID = "my-wifi-ssid";
const char* WIFI_PASS = "my-wifi-pass";

// Losant credentials.
const char* LOSANT_DEVICE_ID = "my-device-id";
const char* LOSANT_ACCESS_KEY = "my-app-key";
const char* LOSANT_ACCESS_SECRET = "my-app-secret";

const int BUTTON_PIN = 5;
const int LED_PIN = 13;
#define DHTPIN D2 
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
bool ledState = false;



WiFiClientSecure wifiClient;

LosantDevice device(LOSANT_DEVICE_ID);

void toggle() {
  Serial.println("Toggling LED.");
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState ? HIGH : LOW);
}

void handleCommand(LosantCommand *command) {
  Serial.print("Command received: ");
  Serial.println(command->name);

  if(strcmp(command->name, "toggle") == 0) {
    toggle();
  }
}

void dhtConnect() {
  Serial.println("DHTxx test!");
  dht.begin();
}

void connect() {

  // Connect to Wifi.
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

   // WiFi fix: https://github.com/esp8266/Arduino/issues/2186
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println();
  Serial.print("Connecting to Losant...");

  device.connectSecure(wifiClient, LOSANT_ACCESS_KEY, LOSANT_ACCESS_SECRET);

  while(!device.connected()) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected!");
  Serial.println("This device is now ready for use!");

    Serial.println("\r\nDHTxx test!");
  dht.begin();
}

void setup() {
  Serial.begin(115200);

  // Giving it a little time because the serial monitor doesn't
  // immediately attach. Want the workshop that's running to
  // appear on each upload.
  delay(2000);

  Serial.println();
  Serial.println("Running Workshop 3.alt Firmware.");

  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  device.onCommand(&handleCommand);
  connect();
}

void buttonPressed() {
  Serial.println("Button Pressed!");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["button"] = true;
  device.sendState(root);
}

void reportTemp(double degreesC, double degreesF, double Humidity) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["tempC"] = degreesC;
  root["tempF"] = degreesF;
  root["humid"] = Humidity;
  device.sendState(root);
}

int buttonState = 0;

int timeSinceLastRead = 0;
float tempSum = 0;
int tempCount = 0;

void loop() {

  bool toReconnect = false;

  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Disconnected from WiFi");
    toReconnect = true;
  }

  if(!device.connected()) {
    Serial.println("Disconnected from MQTT");
    Serial.println(device.mqttClient.state());
    toReconnect = true;
  }

  if(toReconnect) {
    connect();
  }

  device.loop();

  int currentRead = digitalRead(BUTTON_PIN);

  if(currentRead != buttonState) {
    buttonState = currentRead;
    if(buttonState) {
      buttonPressed();
    }
  }

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  tempCount++;

  // Report every 15 seconds.
  if(timeSinceLastRead > 2000) {
   
    Serial.println();
    Serial.print("Temperature C: ");
    Serial.println(t);
    Serial.print("Temperature F: ");
    Serial.println(f);
        Serial.print("Humidity: ");
    Serial.println(h);
    Serial.println();

    reportTemp(t, f, h);

    timeSinceLastRead = 0;
    tempSum = 0;
    tempCount = 0;
  }

  delay(100);
  timeSinceLastRead += 100;
}
