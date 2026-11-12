# Cloud-Connected Security Node (IoT Telemetry)

## Project Overview
The Cloud-Connected Security Node is an IoT-based security monitoring system developed using ESP32. It uses an ultrasonic sensor to detect nearby objects and identify possible intrusion events. The detected distance and security status are sent to the Adafruit IO cloud dashboard using MQTT communication.

## Objectives
- Detect nearby objects using an ultrasonic sensor.
- Identify possible intrusion events.
- Provide alerts using an LED and buzzer.
- Send real-time sensor data to a cloud dashboard.
- Monitor security status remotely.

## Components Used
- ESP32 Development Board
- HC-SR04 Ultrasonic Sensor
- LED
- Buzzer

## Software and Technologies
- Arduino IDE
- Wokwi Simulator
- Adafruit IO
- MQTT Protocol
- Embedded C/C++

## Working Principle
1. The ultrasonic sensor measures the distance of nearby objects.
2. ESP32 processes the measured distance.
3. If the distance is below 50 cm, the LED and buzzer are activated.
4. If the area is clear, the LED and buzzer remain OFF.
5. Distance and security status are published to Adafruit IO using MQTT.

## Cloud Monitoring
The Adafruit IO dashboard displays:
- Distance readings
- Security status
- Intruder alert information

## Applications
- Basic security monitoring
- Smart home security systems
- Restricted-area monitoring
- IoT-based surveillance systems

## Future Improvements
- Add camera-based monitoring.
- Introduce mobile notifications.
- Improve detection range and accuracy.

## Author
Vinothini S

## Project Status
Simulation and cloud telemetry implementation.

