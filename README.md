# Gesture-Controlled RC Car

An ESP32-based wireless RC car controlled through hand gestures using an MPU6050 accelerometer and ESP-NOW communication.

The project uses two ESP32 boards: one as the gesture-controlled transmitter and another as the receiver responsible for motor control. Tilting the transmitter changes the detected acceleration values, which are mapped to forward, backward, left, right, or stop commands.

---

## Project Images

### Robot

| | |
|---|---|
| ![](./pic/pic1.jpeg) | ![](./pic/pic3.jpeg) |
| ![](./pic/pic2.jpeg) | ![](./pic/pic4.jpeg) |
| | |

---

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

---

## Hardware Components

| Component | Quantity |
|-----------|----------|
| ESP32 Development Boards | 2 |
| MPU6050 Accelerometer/Gyroscope | 1 |
| Motor Driver | 1 |
| DC Motors | 2 |
| Robotic Car Chassis | 1 |
| Battery / Power Supply | As required |
| Connecting Wires | As required |

---

# Transmitter

## Overview

The transmitter consists of an ESP32 and an MPU6050 motion sensor.

The MPU6050 detects the movement and tilt of the transmitter. The ESP32 processes the acceleration values and converts them into movement commands. These commands are then sent wirelessly to the receiver using ESP-NOW.

## Transmitter Components

| Component | Quantity |
|-----------|----------|
| ESP32 Development Board | 1 |
| MPU6050 | 1 |
| Connecting Wires | As required |

## Transmitter Wiring

The transmitter uses I2C communication between the ESP32 and MPU6050.

| MPU6050 | ESP32 |
|---------|-------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 3 |
| SCL | GPIO 4 |

![Transmitter Wiring Diagram](./wiring%20diagrams/transmitter.png)

## Transmitter Control Logic

The transmitter determines the direction using the X and Y acceleration values from the MPU6050.

| Sensor Condition | Command |
|------------------|---------|
| Y-axis > dead zone | Forward |
| Y-axis < -dead zone | Backward |
| X-axis > dead zone | Right |
| X-axis < -dead zone | Left |
| Within dead zone | Stop |

The configured dead-zone value is:

```cpp
int deadZone = 3000;
```

The dead zone can be adjusted to change the sensitivity of gesture detection.

## Direction Mapping

The transmitted commands use the following values:

```text
0 = STOP
1 = FORWARD
2 = BACKWARD
3 = LEFT
4 = RIGHT
```

---

# Receiver

## Overview

The receiver consists of an ESP32 and a motor driver connected to two DC motors.

The receiver ESP32 receives movement commands from the transmitter through ESP-NOW. It then interprets the command and controls the motor driver to move the vehicle in the requested direction.

## Receiver Components

| Component | Quantity |
|-----------|----------|
| ESP32 Development Board | 1 |
| Motor Driver | 1 |
| DC Motors | 2 |
| Battery / Power Supply | As required |

## Receiver Wiring

![Receiver Wiring Diagram](./wiring%20diagrams/receiver.png)

The receiver motor-control pins are configured as follows:

| Function | GPIO |
|----------|------|
| PWMA | 2 |
| AIN1 | 3 |
| AIN2 | 4 |
| STBY | 5 |
| BIN1 | 8 |
| BIN2 | 9 |
| PWMB | 10 |

The physical wiring should match these GPIO definitions. If the wiring is changed, update the corresponding pin definitions in `receiver.ino`.

## Motor Control

### Forward

Both motors rotate in the forward direction.

### Backward

Both motors rotate in the reverse direction.

### Left

The motors rotate in opposite directions to pivot the vehicle to the left.

### Right

The motors rotate in opposite directions to pivot the vehicle to the right.

### Stop

Both motor outputs are set to zero.

The configured maximum motor speed is:

```cpp
#define MAX_SPEED 130
```

This value can be adjusted according to the motor characteristics, power supply, and required speed.

---

# Wireless Communication

The transmitter and receiver communicate using ESP-NOW.

## Transmitter Process

1. Initialize the ESP32.
2. Initialize the MPU6050.
3. Configure Wi-Fi in station mode.
4. Initialize ESP-NOW.
5. Register the receiver ESP32 as an ESP-NOW peer.
6. Read acceleration values from the MPU6050.
7. Determine the movement direction.
8. Send the movement command to the receiver.

## Receiver Process

1. Initialize the ESP32.
2. Configure Wi-Fi in station mode.
3. Initialize ESP-NOW.
4. Register the receive callback.
5. Receive the movement command.
6. Validate the received data.
7. Select the corresponding motor-control function.
8. Drive the motors through the motor driver.

The current implementation uses Wi-Fi channel 1 and an unencrypted ESP-NOW peer connection.

---

# System Architecture

```text
                       TRANSMITTER

                  MPU6050 Motion Sensor
                           |
                           v
                         ESP32
                           |
                           | ESP-NOW
                           |
                           v

                        RECEIVER

                         ESP32
                           |
                           v
                     Motor Driver
                       /       \
                      v         v
                  DC Motor   DC Motor
```

---

# Working Principle

1. The user tilts the transmitter.
2. The MPU6050 detects the resulting acceleration.
3. The transmitter ESP32 reads the X and Y acceleration values.
4. The acceleration values are compared with the configured dead zone.
5. A movement command is selected.
6. The command is transmitted to the receiver using ESP-NOW.
7. The receiver ESP32 processes the received command.
8. The motor driver controls the two DC motors.
9. The vehicle moves according to the detected gesture.

---

# Project Structure

```text
Gesture-control-rc-car/
│
├── code/
│   ├── receiver.ino
│   └── transmitter.ino
│
├── pic/
│   ├── pic1.jpeg
│   ├── pic2.jpeg
│   ├── pic3.jpeg
│   └── pic4.jpeg
│
├── wiring diagrams/
│   ├── transmitter.png
│   └── receiver.png
│
└── README.md
```

---

# Getting Started

## Prerequisites

Install the following:

- Arduino IDE
- ESP32 board support package
- Wire library
- MPU6050 library

Hardware required:

- Two ESP32 development boards
- One MPU6050 sensor
- One compatible motor driver
- Two DC motors
- Robotic car chassis
- Suitable power supply
- Connecting wires

## Clone the Repository

```bash
git clone https://github.com/yo5on/Gesture-control-rc-car.git
cd Gesture-control-rc-car
```

## Configure the Transmitter

Open:

```text
code/transmitter.ino
```

Verify that the receiver ESP32 MAC address configured in the transmitter code is correct.

Upload the transmitter code to the ESP32 connected to the MPU6050.

## Configure the Receiver

Open:

```text
code/receiver.ino
```

Verify the motor-driver GPIO configuration and upload the code to the second ESP32.

## Serial Monitor

Open the Arduino IDE Serial Monitor at:

```text
115200 baud
```

The transmitter can report messages such as:

```text
MPU6050 OK
ESP-NOW READY
TX: FORWARD
TX: BACKWARD
TX: LEFT
TX: RIGHT
TX: STOP
```

The receiver reports the corresponding motor commands for debugging.

---

# Safety and Power Considerations

- Use an appropriate power supply for the ESP32, motor driver, and motors.
- Do not power high-current motors directly from ESP32 GPIO pins.
- Ensure the motor driver and ESP32 have an appropriate common ground.
- Verify motor polarity before testing directional controls.
- Secure the battery and wiring before operating the vehicle.
- Test the vehicle at low speed before increasing the motor speed.

---

# Troubleshooting

## ESP-NOW Communication Fails

Check:

- Both ESP32 boards are powered correctly.
- The receiver MAC address is correct.
- Both devices use the same Wi-Fi channel.
- ESP-NOW initialization succeeds.
- The receiver is registered as a peer on the transmitter.

## MPU6050 Is Not Detected

Check:

- SDA and SCL connections.
- Power and ground connections.
- I2C pin configuration.
- MPU6050 library installation.

## Motors Do Not Move

Check:

- Motor-driver wiring.
- Motor-driver power supply.
- STBY configuration.
- Motor connections.
- GPIO definitions in `receiver.ino`.

## Vehicle Moves in the Wrong Direction

Check the motor polarity and direction-control logic in the receiver code. Swap the motor connections or update the corresponding motor-control logic if required.

---

# Future Improvements

Potential improvements include:

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

---

# Technologies

| Category | Technology |
|----------|------------|
| Microcontrollers | ESP32 |
| Programming | C/C++ |
| Motion Sensor | MPU6050 |
| Wireless Communication | ESP-NOW |
| Motor Control | Motor Driver |
| Motors | DC Motors |
| Development Environment | Arduino IDE |
| Communication Interface | I2C |

---

# Author

**Yoson**

Computer Science student interested in AI/ML, robotics, embedded systems, and automation.

GitHub: https://github.com/yo5on

---

# License

This project is intended for educational and personal use. You are free to explore, modify, and extend the project for your own robotics and embedded systems experiments.

If you find this project useful, consider giving the repository a star.
