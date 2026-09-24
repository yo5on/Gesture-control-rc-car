#include <WiFi.h>
#include <esp_now.h>

// ===== Motor Pins =====
#define PWMA 2
#define AIN1 3
#define AIN2 4
#define STBY 5
#define BIN1 8
#define BIN2 9
#define PWMB 10

// Reduced speed for 3V motors
#define MAX_SPEED 130

typedef struct {
  int dir;   // 0=STOP, 1=FWD, 2=BACK, 3=LEFT, 4=RIGHT
} ControlData;

ControlData data;

// ================= MOTOR FUNCTIONS =================

void stopMotors() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
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

// Pivot left
void right() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);

  analogWrite(PWMA, MAX_SPEED);
  analogWrite(PWMB, MAX_SPEED);

  Serial.println("LEFT PIVOT");
}

// Pivot right
void left() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);

  analogWrite(PWMA, MAX_SPEED);
  analogWrite(PWMB, MAX_SPEED);

  Serial.println("RIGHT PIVOT");
}

// ================= ESP-NOW RECEIVE =================

void onReceive(const uint8_t *mac, const uint8_t *incomingData, int len) {

  if (len != sizeof(ControlData)) return;

  memcpy(&data, incomingData, sizeof(data));

  switch (data.dir) {
    case 1: forward(); break;
    case 2: backward(); break;
    case 3: left(); break;
    case 4: right(); break;
    default: stopMotors(); break;
  }
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

  digitalWrite(STBY, HIGH);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_recv_cb(onReceive);

  Serial.println("Receiver READY");
}

void loop() {
}
