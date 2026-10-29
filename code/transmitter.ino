#include <Wire.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <MPU6050.h>

#define SDA_PIN 3
#define SCL_PIN 4

MPU6050 mpu;

// RECEIVER MAC ADDRESS
uint8_t receiverMAC[] = {0x1C, 0xDB, 0xD4, 0x3A, 0x6E, 0xB0};

typedef struct {
  int dir;   // 0=STOP,1=FWD,2=BACK,3=LEFT,4=RIGHT
} ControlData;

ControlData data;
bool espNowReady = false;

int16_t ax, ay, az;
int deadZone = 3000;

// ===== ESP-NOW INIT =====
bool initEspNow() {

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    return false;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 1;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Peer Add Failed");
    esp_now_deinit();
    return false;
  }

  Serial.println("ESP-NOW READY");
  return true;
}

void setup() {

  Serial.begin(115200);
  delay(2000);

  Wire.begin(SDA_PIN, SCL_PIN);
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 NOT detected");
    while (1);
  }

  Serial.println("MPU6050 OK");

  espNowReady = initEspNow();
}

void loop() {

  mpu.getAcceleration(&ax, &ay, &az);

  if (ay > deadZone) {
    data.dir = 1;
    Serial.println("TX: FORWARD");
  }

  else if (ay < -deadZone) {
    data.dir = 2;
    Serial.println("TX: BACKWARD");
  }

  else if (ax > deadZone) {
    data.dir = 4;
    Serial.println("TX: RIGHT");
  }

  else if (ax < -deadZone) {
    data.dir = 3;
    Serial.println("TX: LEFT");
  }

  else {
    data.dir = 0;
    Serial.println("TX: STOP");
  }

  if (espNowReady) {
    const esp_err_t result = esp_now_send(receiverMAC, (uint8_t *)&data, sizeof(data));
    if (result != ESP_OK) {
      static unsigned long lastSendErrorAt = 0;
      if (millis() - lastSendErrorAt >= 2000) {
        Serial.println("ESP-NOW send could not be queued; check receiver MAC/channel");
        lastSendErrorAt = millis();
      }
    }
  }

  delay(70);
}
