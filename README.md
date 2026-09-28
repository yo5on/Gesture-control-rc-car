<div align="center">

<img src="https://raw.githubusercontent.com/yo5on/yo5on/main/hd-projects.svg" width="620" alt="projects"/>

<samp><b>GESTURE-CONTROLLED RC CAR</b></samp>

<samp>esp32 · mpu6050 · esp-now · embedded systems</samp>

**[Repository](https://github.com/yo5on/Gesture-control-rc-car)**

</div>

---

<samp>An ESP32-based wireless RC car controlled through hand gestures using an MPU6050 accelerometer and ESP-NOW communication.</samp>

<samp><b>Overview</b></samp>

<samp>The project uses two ESP32 boards: one as the gesture-controlled transmitter and another as the receiver responsible for motor control. Tilting the transmitter changes the detected acceleration values, which are mapped to forward, backward, left, right, or stop commands.</samp>

<samp><b>Project Images</b></samp>

| | |
|---|---|
| ![](./pic/pic1.jpeg) | ![](./pic/pic3.jpeg) |
| ![](./pic/pic2.jpeg) | ![](./pic/pic4.jpeg) |

<samp><b>Features</b></samp>

- <samp>Gesture-based directional control</samp>
- <samp>Wireless communication using ESP-NOW</samp>
- <samp>MPU6050 accelerometer input</samp>
- <samp>Forward and backward movement</samp>
- <samp>Left and right pivot control</samp>
- <samp>Configurable movement dead zone</samp>
- <samp>Dual-motor control</samp>
- <samp>Adjustable motor speed</samp>
- <samp>Serial output for debugging</samp>
- <samp>Two-ESP32 transmitter and receiver architecture</samp>

<samp><b>Hardware Components</b></samp>

| Component | Quantity |
|---|---:|
| ESP32 Development Boards | 2 |
| MPU6050 Accelerometer/Gyroscope | 1 |
| Motor Driver | 1 |
| DC Motors | 2 |
| Robotic Car Chassis | 1 |
| Battery / Power Supply | As required |
| Connecting Wires | As required |

<samp><b>Transmitter</b></samp>

<samp>The transmitter consists of an ESP32 and an MPU6050 motion sensor. The MPU6050 detects movement and tilt, the ESP32 converts acceleration values into movement commands, and ESP-NOW sends those commands wirelessly to the receiver.</samp>

<samp><b>Wiring</b></samp>

| MPU6050 | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 3 |
| SCL | GPIO 4 |

![Transmitter Wiring Diagram](./wiring%20diagrams/transmitter.png)

<samp><b>Direction Logic</b></samp>

| Sensor Condition | Command |
|---|---|
| Y-axis > dead zone | Forward |
| Y-axis < -dead zone | Backward |
| X-axis > dead zone | Right |
| X-axis < -dead zone | Left |
| Within dead zone | Stop |

```cpp
int deadZone = 3000;
```

<samp><b>Direction Mapping</b></samp>

```text
0 = STOP
1 = FORWARD
2 = BACKWARD
3 = LEFT
4 = RIGHT
```

<samp><b>Receiver</b></samp>

<samp>The receiver consists of an ESP32 and a motor driver connected to two DC motors. It receives commands through ESP-NOW and controls the motor driver accordingly.</samp>

<samp><b>Wiring</b></samp>

![Receiver Wiring Diagram](./wiring%20diagrams/receiver.png)

| Function | GPIO |
|---|---:|
| PWMA | 2 |
| AIN1 | 3 |
| AIN2 | 4 |
| STBY | 5 |
| BIN1 | 8 |
| BIN2 | 9 |
| PWMB | 10 |

<samp><b>Motor Control</b></samp>

<samp>The vehicle supports forward, backward, left, right, and stop states. The configured maximum motor speed is:</samp>

```cpp
#define MAX_SPEED 130
```

<samp><b>Wireless Communication</b></samp>

<samp>The transmitter and receiver communicate using ESP-NOW.</samp>

```text
Transmitter
    |
    | ESP-NOW
    v
Receiver
    |
    v
Motor Driver
   / \
  v   v
Motor Motor
```

<samp>The current implementation uses Wi-Fi channel 1 and an unencrypted ESP-NOW peer connection.</samp>

<samp><b>Working Principle</b></samp>

1. <samp>The user tilts the transmitter.</samp>
2. <samp>The MPU6050 detects the resulting acceleration.</samp>
3. <samp>The transmitter ESP32 reads the X and Y acceleration values.</samp>
4. <samp>The values are compared with the configured dead zone.</samp>
5. <samp>A movement command is selected.</samp>
6. <samp>The command is transmitted using ESP-NOW.</samp>
7. <samp>The receiver ESP32 processes the command.</samp>
8. <samp>The motor driver controls the two DC motors.</samp>

<samp><b>Project Structure</b></samp>

```text
Gesture-control-rc-car/
├── code/
│   ├── receiver.ino
│   └── transmitter.ino
├── pic/
│   ├── pic1.jpeg
│   ├── pic2.jpeg
│   ├── pic3.jpeg
│   └── pic4.jpeg
├── wiring diagrams/
│   ├── transmitter.png
│   └── receiver.png
└── README.md
```

<samp><b>Getting Started</b></samp>

<samp><b>Prerequisites</b></samp>

- <samp>Arduino IDE</samp>
- <samp>ESP32 board support package</samp>
- <samp>Wire library</samp>
- <samp>MPU6050 library</samp>
- <samp>Two ESP32 development boards</samp>
- <samp>MPU6050 sensor</samp>
- <samp>Compatible motor driver</samp>
- <samp>Two DC motors</samp>
- <samp>Robotic car chassis</samp>
- <samp>Suitable power supply</samp>

<samp><b>Clone</b></samp>

```bash
git clone https://github.com/yo5on/Gesture-control-rc-car.git
cd Gesture-control-rc-car
```

<samp><b>Transmitter</b></samp>

<samp>Open <code>code/transmitter.ino</code>, verify the receiver ESP32 MAC address, and upload it to the ESP32 connected to the MPU6050.</samp>

<samp><b>Receiver</b></samp>

<samp>Open <code>code/receiver.ino</code>, verify the motor-driver GPIO configuration, and upload it to the second ESP32.</samp>

<samp><b>Serial Monitor</b></samp>

<samp>Use the Arduino IDE Serial Monitor at <code>115200</code> baud for transmitter and receiver diagnostics.</samp>

<samp><b>Safety and Power Considerations</b></samp>

- <samp>Use an appropriate power supply for the ESP32, motor driver, and motors.</samp>
- <samp>Do not power high-current motors directly from ESP32 GPIO pins.</samp>
- <samp>Ensure the motor driver and ESP32 have an appropriate common ground.</samp>
- <samp>Verify motor polarity before testing directional controls.</samp>
- <samp>Secure the battery and wiring before operating the vehicle.</samp>
- <samp>Test at low speed before increasing motor speed.</samp>

<samp><b>Troubleshooting</b></samp>

<samp><b>ESP-NOW Communication Fails</b></samp>

<samp>Check power, receiver MAC address, Wi-Fi channel, ESP-NOW initialization, and peer registration.</samp>

<samp><b>MPU6050 Is Not Detected</b></samp>

<samp>Check SDA/SCL, power, ground, I2C configuration, and library installation.</samp>

<samp><b>Motors Do Not Move</b></samp>

<samp>Check motor-driver wiring, motor-driver power, STBY configuration, motor connections, and GPIO definitions.</samp>

<samp><b>Future Improvements</b></samp>

- <samp>Adjustable gesture sensitivity</samp>
- <samp>Speed control based on tilt angle</samp>
- <samp>Smoother acceleration and deceleration</samp>
- <samp>Mobile application control</samp>
- <samp>Battery voltage monitoring</samp>
- <samp>OLED telemetry display</samp>
- <samp>Obstacle detection</samp>
- <samp>Autonomous navigation</samp>
- <samp>Camera integration</samp>
- <samp>Improved wireless security</samp>
- <samp>Additional gesture-based control modes</samp>

<samp><b>Technologies</b></samp>

| Category | Technology |
|---|---|
| Microcontrollers | ESP32 |
| Programming | C/C++ |
| Motion Sensor | MPU6050 |
| Wireless Communication | ESP-NOW |
| Motor Control | Motor Driver |
| Motors | DC Motors |
| Development Environment | Arduino IDE |
| Communication Interface | I2C |

<samp><b>Author</b></samp>

<samp><b>Yoson</b></samp>

<samp>Computer Science student interested in AI/ML, robotics, embedded systems, and automation.</samp>

<samp>GitHub: https://github.com/yo5on</samp>

<samp><b>License</b></samp>

<samp>This project is intended for educational and personal use. You are free to explore, modify, and extend the project for robotics and embedded systems experiments.</samp>
