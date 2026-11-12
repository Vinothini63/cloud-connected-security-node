
#include <WiFi.h>
#include <PubSubClient.h>

#define TRIG_PIN 5
#define ECHO_PIN 18
#define LED_PIN 19
#define BUZZER_PIN 23

// WiFi settings for Wokwi
const char* ssid = "Wokwi-GUEST";
const char* wifiPassword = "";

// Adafruit IO credentials
const char* aioUsername = "vinothini03";
const char* aioKey = "YOUR_ADAFRUIT_IO_KEY";

// MQTT settings
const char* mqttServer = "io.adafruit.com";
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

long duration;
float distance;

void connectWiFi() {
  WiFi.begin(ssid, wifiPassword);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
}

void connectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to Adafruit IO...");

    if (client.connect("ESP32SecurityNode", aioUsername, aioKey)) {
      Serial.println("Connected!");
    } else {
      Serial.print("Failed. State: ");
      Serial.println(client.state());
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  connectWiFi();

  client.setServer(mqttServer, mqttPort);

  Serial.println("IoT Security Node Started");
}

void loop() {
  if (!client.connected()) {
    connectMQTT();
  }

  client.loop();

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration > 0) {
    distance = duration * 0.0343 / 2;

    String status;

    if (distance < 50) {
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
      status = "INTRUDER ALERT";
    } else {
      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      status = "AREA CLEAR";
    }

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    Serial.println(status);

    client.publish("vinothini03/feeds/security-distance",
                   String(distance, 2).c_str());

    client.publish("vinothini03/feeds/security-status",
                   status.c_str());
  }

  delay(2000);
}
