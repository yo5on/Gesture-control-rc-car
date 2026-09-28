<div align="center">

<img src="https://raw.githubusercontent.com/yo5on/yo5on/main/hd-projects.svg" width="620" alt="projects"/>

<samp><b>GESTURE-CONTROLLED RC CAR</b></samp>

<samp>esp32 · mpu6050 · esp-now · embedded systems</samp>

</div>

---

<div align="center"><samp>An ESP32-based wireless RC car controlled through hand gestures using an MPU6050 accelerometer and ESP-NOW communication.</samp></div>

---

<div align="center"><samp><b>Project Overview</b></samp></div>

<samp>The project uses two ESP32 boards: one as the gesture-controlled transmitter and another as the receiver responsible for motor control.</samp>

<samp>Tilting the transmitter changes the detected acceleration values, which are mapped to forward, backward, left, right, or stop commands.</samp>

<samp>The project provides practical experience with:</samp>

- <samp>Gesture-based control</samp>
- <samp>Wireless communication</samp>
- <samp>Motion sensing</samp>
- <samp>Motor control</samp>
- <samp>Embedded systems</samp>
- <samp>Real-time data processing</samp>

---

<div align="center"><samp><b>Project Images</b></samp></div>

<table align="center">
<tr><th><samp>RC Car</samp></th><th><samp>Project</samp></th></tr>
<tr><td><img src="pic/pic1.jpeg" alt="RC Car"></td><td><img src="pic/pic3.jpeg" alt="Gesture Control RC Car"></td></tr>
<tr><td><img src="pic/pic2.jpeg" alt="RC Car Project"></td><td><img src="pic/pic4.jpeg" alt="Gesture Control Project"></td></tr>
</table>

---

<div align="center"><samp><b>Features</b></samp></div>

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

---

<div align="center"><samp><b>Hardware Components</b></samp></div>

<table align="center">
<tr><th><samp>Component</samp></th><th><samp>Quantity</samp></th></tr>
<tr><td><samp>ESP32 Development Boards</samp></td><td><samp>2</samp></td></tr>
<tr><td><samp>MPU6050 Accelerometer/Gyroscope</samp></td><td><samp>1</samp></td></tr>
<tr><td><samp>Motor Driver</samp></td><td><samp>1</samp></td></tr>
<tr><td><samp>DC Motors</samp></td><td><samp>2</samp></td></tr>
<tr><td><samp>Robotic Car Chassis</samp></td><td><samp>1</samp></td></tr>
<tr><td><samp>Battery / Power Supply</samp></td><td><samp>As required</samp></td></tr>
<tr><td><samp>Connecting Wires</samp></td><td><samp>As required</samp></td></tr>
</table>

---

<div align="center"><samp><b>Transmitter</b></samp></div>

<samp>The transmitter consists of an ESP32 and an MPU6050 motion sensor. The MPU6050 detects movement and tilt, the ESP32 converts acceleration values into movement commands, and ESP-NOW sends those commands wirelessly to the receiver.</samp>

<div align="center"><img src="wiring%20diagrams/transmitter.png" alt="Transmitter Wiring Diagram" width="80%"></div>

---

<div align="center"><samp><b>Transmitter Wiring</b></samp></div>

<table align="center">
<tr><th><samp>MPU6050</samp></th><th><samp>ESP32</samp></th></tr>
<tr><td><samp>VCC</samp></td><td><samp>3.3V</samp></td></tr>
<tr><td><samp>GND</samp></td><td><samp>GND</samp></td></tr>
<tr><td><samp>SDA</samp></td><td><samp>GPIO 3</samp></td></tr>
<tr><td><samp>SCL</samp></td><td><samp>GPIO 4</samp></td></tr>
</table>

---

<div align="center"><samp><b>Direction Logic</b></samp></div>

<table align="center">
<tr><th><samp>Sensor Condition</samp></th><th><samp>Command</samp></th></tr>
<tr><td><samp>Y-axis &gt; dead zone</samp></td><td><samp>Forward</samp></td></tr>
<tr><td><samp>Y-axis &lt; -dead zone</samp></td><td><samp>Backward</samp></td></tr>
<tr><td><samp>X-axis &gt; dead zone</samp></td><td><samp>Right</samp></td></tr>
<tr><td><samp>X-axis &lt; -dead zone</samp></td><td><samp>Left</samp></td></tr>
<tr><td><samp>Within dead zone</samp></td><td><samp>Stop</samp></td></tr>
</table>

```cpp
int deadZone = 3000;
```

<div align="center"><samp><b>Direction Mapping</b></samp></div>

```text
0 = STOP
1 = FORWARD
2 = BACKWARD
3 = LEFT
4 = RIGHT
```

---

<div align="center"><samp><b>Receiver</b></samp></div>

<samp>The receiver consists of an ESP32 and a motor driver connected to two DC motors. It receives commands through ESP-NOW and controls the motor driver accordingly.</samp>

<div align="center"><img src="wiring%20diagrams/receiver.png" alt="Receiver Wiring Diagram" width="80%"></div>

---

<div align="center"><samp><b>Receiver Wiring</b></samp></div>

<table align="center">
<tr><th><samp>Function</samp></th><th><samp>GPIO</samp></th></tr>
<tr><td><samp>PWMA</samp></td><td><samp>2</samp></td></tr>
<tr><td><samp>AIN1</samp></td><td><samp>3</samp></td></tr>
<tr><td><samp>AIN2</samp></td><td><samp>4</samp></td></tr>
<tr><td><samp>STBY</samp></td><td><samp>5</samp></td></tr>
<tr><td><samp>BIN1</samp></td><td><samp>8</samp></td></tr>
<tr><td><samp>BIN2</samp></td><td><samp>9</samp></td></tr>
<tr><td><samp>PWMB</samp></td><td><samp>10</samp></td></tr>
</table>

---

<div align="center"><samp><b>Motor Control</b></samp></div>

<samp>The vehicle supports forward, backward, left, right, and stop states. The configured maximum motor speed is:</samp>

```cpp
#define MAX_SPEED 130
```

---

<div align="center"><samp><b>Wireless Communication</b></samp></div>

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

---

<div align="center"><samp><b>Working Principle</b></samp></div>

<samp>1. The user tilts the transmitter.</samp>
<samp>2. The MPU6050 detects the resulting acceleration.</samp>
<samp>3. The transmitter ESP32 reads the X and Y acceleration values.</samp>
<samp>4. The values are compared with the configured dead zone.</samp>
<samp>5. A movement command is selected.</samp>
<samp>6. The command is transmitted using ESP-NOW.</samp>
<samp>7. The receiver ESP32 processes the command.</samp>
<samp>8. The motor driver controls the two DC motors.</samp>

---

<div align="center"><samp><b>Project Structure</b></samp></div>

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

---

<div align="center"><samp><b>Getting Started</b></samp></div>

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

<samp><b>Clone the Repository</b></samp>

```bash
git clone https://github.com/yo5on/Gesture-control-rc-car.git
cd Gesture-control-rc-car
```

<samp><b>Configure the Transmitter</b></samp>

<samp>Open <code>code/transmitter.ino</code>, verify the receiver ESP32 MAC address, and upload it to the ESP32 connected to the MPU6050.</samp>

<samp><b>Configure the Receiver</b></samp>

<samp>Open <code>code/receiver.ino</code>, verify the motor-driver GPIO configuration, and upload it to the second ESP32.</samp>

<samp><b>Serial Monitor</b></samp>

<samp>Use the Arduino IDE Serial Monitor at <code>115200</code> baud for transmitter and receiver diagnostics.</samp>

---

<div align="center"><samp><b>Safety and Power Considerations</b></samp></div>

- <samp>Use an appropriate power supply for the ESP32, motor driver, and motors.</samp>
- <samp>Do not power high-current motors directly from ESP32 GPIO pins.</samp>
- <samp>Ensure the motor driver and ESP32 have an appropriate common ground.</samp>
- <samp>Verify motor polarity before testing directional controls.</samp>
- <samp>Secure the battery and wiring before operating the vehicle.</samp>
- <samp>Test at low speed before increasing motor speed.</samp>

---

<div align="center"><samp><b>Troubleshooting</b></samp></div>

<samp><b>ESP-NOW communication fails</b></samp>

<samp>Check power, receiver MAC address, Wi-Fi channel, ESP-NOW initialization, and peer registration.</samp>

<samp><b>MPU6050 is not detected</b></samp>

<samp>Check SDA/SCL, power, ground, I2C configuration, and library installation.</samp>

<samp><b>Motors do not move</b></samp>

<samp>Check motor-driver wiring, motor-driver power, STBY configuration, motor connections, and GPIO definitions.</samp>

---

<div align="center"><samp><b>Future Improvements</b></samp></div>

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

---

<div align="center"><samp><b>Technologies</b></samp></div>

<table align="center">
<tr><th><samp>Category</samp></th><th><samp>Technology</samp></th></tr>
<tr><td><samp>Microcontrollers</samp></td><td><samp>ESP32</samp></td></tr>
<tr><td><samp>Programming</samp></td><td><samp>C/C++</samp></td></tr>
<tr><td><samp>Motion Sensor</samp></td><td><samp>MPU6050</samp></td></tr>
<tr><td><samp>Wireless Communication</samp></td><td><samp>ESP-NOW</samp></td></tr>
<tr><td><samp>Motor Control</samp></td><td><samp>Motor Driver</samp></td></tr>
<tr><td><samp>Motors</samp></td><td><samp>DC Motors</samp></td></tr>
<tr><td><samp>Development Environment</samp></td><td><samp>Arduino IDE</samp></td></tr>
<tr><td><samp>Communication Interface</samp></td><td><samp>I2C</samp></td></tr>
</table>

---

<div align="center"><samp><b>Author</b></samp></div>

<div align="center">
<samp><strong>Yoson</strong></samp>

<samp>Computer Science student interested in AI/ML, robotics, embedded systems, and automation.</samp>

<samp>GitHub: https://github.com/yo5on</samp>
</div>

---

<div align="center"><samp><b>License</b></samp></div>

<samp>This project is intended for educational and personal use. You are free to explore, modify, and extend the project for robotics and embedded systems experiments.</samp>

<div align="center"><samp>If you find this project useful, consider giving the repository a star.</samp></div>
