<div align="center">

<img src="https://raw.githubusercontent.com/yo5on/yo5on/main/hd-projects.svg" width="620" alt="projects"/>

<samp><b>GESTURE-CONTROLLED RC CAR</b></samp>

<samp>esp32 · mpu6050 · esp-now · embedded systems</samp>

**[Repository](https://github.com/yo5on/Gesture-control-rc-car)**

</div>

---

An ESP32-based wireless RC car controlled through hand gestures using an MPU6050 accelerometer and ESP-NOW communication.

## Overview

The project uses two ESP32 boards: one as the gesture-controlled transmitter and another as the receiver responsible for motor control. Tilting the transmitter changes the detected acceleration values, which are mapped to forward, backward, left, right, or stop commands.

## Project Images

| | |
|---|---|
| ![](./pic/pic1.jpeg) | ![](./pic/pic3.jpeg) |
| ![](./pic/pic2.jpeg) | ![](./pic/pic4.jpeg) |

## Features

- Gesture-based directional control
- Wireless communication using ESP-NOW
- MPU6050 accelerometer input
- Forward and backward movement
- Left and right pivot control
- Configurable movement dead zone
- Dual-motor control
- Adjustable motor speed
- Serial output for debugging
- Two-ESP32 transmitter and receiver architecture

## Hardware Components

| Component | Quantity |
|---|---:|
| ESP32 Development Boards | 2 |
| MPU6050 Accelerometer/Gyroscope | 1 |
| Motor Driver | 1 |
| DC Motors | 2 |
| Robotic Car Chassis | 1 |
| Battery / Power Supply | As required |
| Connecting Wires | As required |

## Transmitter

The transmitter consists of an ESP32 and an MPU6050 motion sensor. The MPU6050 detects movement and tilt, the ESP32 converts acceleration values into movement commands, and ESP-NOW sends those commands wirelessly to the receiver.

### Wiring

| MPU6050 | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 3 |
| SCL | GPIO 4 |

![Transmitter Wiring Diagram](./wiring%20diagrams/transmitter.png)

### Direction Logic

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

### Direction Mapping

```text
0 = STOP
1 = FORWARD
2 = BACKWARD
3 = LEFT
4 = RIGHT
```

## Receiver

The receiver consists of an ESP32 and a motor driver connected to two DC motors. It receives commands through ESP-NOW and controls the motor driver accordingly.

### Wiring

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

### Motor Control

The vehicle supports forward, backward, left, right, and stop states. The configured maximum motor speed is:

```cpp
#define MAX_SPEED 130
```

## Wireless Communication

The transmitter and receiver communicate using ESP-NOW.

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

The current implementation uses Wi-Fi channel 1 and an unencrypted ESP-NOW peer connection.

## Working Principle

1. The user tilts the transmitter.
2. The MPU6050 detects the resulting acceleration.
3. The transmitter ESP32 reads the X and Y acceleration values.
4. The values are compared with the configured dead zone.
5. A movement command is selected.
6. The command is transmitted using ESP-NOW.
7. The receiver ESP32 processes the command.
8. The motor driver controls the two DC motors.

## Project Structure

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

## Getting Started

### Prerequisites

- Arduino IDE
- ESP32 board support package
- Wire library
- MPU6050 library
- Two ESP32 development boards
- MPU6050 sensor
- Compatible motor driver
- Two DC motors
- Robotic car chassis
- Suitable power supply

### Clone

```bash
git clone https://github.com/yo5on/Gesture-control-rc-car.git
cd Gesture-control-rc-car
```

### Transmitter

Open `code/transmitter.ino`, verify the receiver ESP32 MAC address, and upload it to the ESP32 connected to the MPU6050.

### Receiver

Open `code/receiver.ino`, verify the motor-driver GPIO configuration, and upload it to the second ESP32.

### Serial Monitor

Use the Arduino IDE Serial Monitor at `115200` baud for transmitter and receiver diagnostics.

## Safety and Power Considerations

- Use an appropriate power supply for the ESP32, motor driver, and motors.
- Do not power high-current motors directly from ESP32 GPIO pins.
- Ensure the motor driver and ESP32 have an appropriate common ground.
- Verify motor polarity before testing directional controls.
- Secure the battery and wiring before operating the vehicle.
- Test at low speed before increasing motor speed.

## Troubleshooting

### ESP-NOW Communication Fails

Check power, receiver MAC address, Wi-Fi channel, ESP-NOW initialization, and peer registration.

### MPU6050 Is Not Detected

Check SDA/SCL, power, ground, I2C configuration, and library installation.

### Motors Do Not Move

Check motor-driver wiring, motor-driver power, STBY configuration, motor connections, and GPIO definitions.

## Future Improvements

- Adjustable gesture sensitivity
- Speed control based on tilt angle
- Smoother acceleration and deceleration
- Mobile application control
- Battery voltage monitoring
- OLED telemetry display
- Obstacle detection
- Autonomous navigation
- Camera integration
- Improved wireless security
- Additional gesture-based control modes

## Technologies

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

## Author

**Yoson**  
Computer Science student interested in AI/ML, robotics, embedded systems, and automation.

GitHub: https://github.com/yo5on

## License

This project is intended for educational and personal use. You are free to explore, modify, and extend the project for robotics and embedded systems experiments.
