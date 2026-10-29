#include <WiFi.h>
#include <esp_now.h>
#include <esp_arduino_version.h>

// ESP32-C3 Super Mini pin map. GPIO 2, 8 and 9 are boot-strapping pins,
// so the motor driver is kept off those pins.
#define PWMA 0
#define AIN1 1
#define AIN2 3
#define STBY 4
#define BIN1 5
#define BIN2 6
#define PWMB 7

// Reduced speed for 3V motors.
#define MAX_SPEED 130
#define RC_TIMEOUT_MS 500UL

typedef struct {
  int dir;   // 0=STOP, 1=FWD, 2=BACK, 3=LEFT, 4=RIGHT
} ControlData;

// Shared with the ESP-NOW callback. The callback only copies state;
// the main loop controls the motor driver.
volatile int receivedDir = 0;
volatile unsigned long lastPacketAt = 0;
int appliedDir = -1;

// ================= MOTOR FUNCTIONS =================

void stopMotors() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  digitalWrite(STBY, LOW);  // disable the TB6612FNG outputs
  Serial.println("STOP");
}

void forward() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, MAX_SPEED);
  analogWrite(PWMB, MAX_SPEED);
  Serial.println("FORWARD");
}

void backward() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMA, MAX_SPEED);
  analogWrite(PWMB, MAX_SPEED);
  Serial.println("BACKWARD");
}

void pivotLeft() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, MAX_SPEED);
  analogWrite(PWMB, MAX_SPEED);
  Serial.println("LEFT PIVOT");
}

void pivotRight() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMA, MAX_SPEED);
  analogWrite(PWMB, MAX_SPEED);
  Serial.println("RIGHT PIVOT");
}

void applyDirection(int direction) {
  if (direction == 0) {
    stopMotors();
    return;
  }

  // PWM is zero after stop, so enabling standby cannot unexpectedly start
  // the previous direction while the new direction pins are being set.
  digitalWrite(STBY, HIGH);
  switch (direction) {
    case 1: forward(); break;
    case 2: backward(); break;
    case 3: pivotLeft(); break;
    case 4: pivotRight(); break;
    default: stopMotors(); break;
  }
}

// ================= ESP-NOW RECEIVE =================

#if ESP_ARDUINO_VERSION_MAJOR >= 3
void onReceive(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
#else
void onReceive(const uint8_t *mac, const uint8_t *incomingData, int len) {
#endif
  if (len != sizeof(ControlData)) return;

  ControlData incoming;
  memcpy(&incoming, incomingData, sizeof(incoming));
  if (incoming.dir < 0 || incoming.dir > 4) return;

  receivedDir = incoming.dir;
  lastPacketAt = millis();
}

// ================= SETUP =================

void setup() {
  Serial.begin(115200);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  // Keep the car stopped until a valid packet arrives.
  stopMotors();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.print("Receiver MAC: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed; motors remain disabled");
    return;
  }

  esp_now_register_recv_cb(onReceive);
  Serial.println("Receiver READY");
}

void loop() {
  const unsigned long now = millis();
  const unsigned long packetAt = lastPacketAt;
  int targetDir = receivedDir;

  // The transmitter normally sends every 70 ms; 500 ms allows several missed
  // packets without letting the car continue moving after a lost connection.
  if (packetAt == 0 || now - packetAt > RC_TIMEOUT_MS) {
    targetDir = 0;
  }

  if (targetDir != appliedDir) {
    applyDirection(targetDir);
    appliedDir = targetDir;
  }
}
