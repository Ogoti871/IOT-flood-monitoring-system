# IoT Flood Monitoring System

## Overview
The IoT Flood Monitoring System is designed to provide real-time monitoring of water levels and assess flood risk using environmental data. The system integrates embedded hardware, sensor data acquisition, and GSM communication to deliver timely alerts when critical thresholds are exceeded. This project demonstrates the practical application of embedded systems and IoT in addressing real-world environmental monitoring challenges.

## System Architecture
The system consists of a microcontroller (Arduino-based), an ultrasonic sensor for water level measurement, an ESP module for communication and data handling, and a GSM A9G module for SMS alerts. It continuously monitors water levels and combines this data with weather conditions to determine flood risk.

## Key Features
- Real-time water level monitoring  
- Threshold-based alert system  
- Integration of weather data for improved risk analysis  
- SMS notification using GSM module  
- Modular and scalable system design  

## System Workflow
1. Initialize hardware components and network modules  
2. Continuously monitor water level using ultrasonic sensor  
3. Evaluate water level against predefined threshold 
4. Fetch relevant weather data  
5. Analyze combined data to determine flood risk  
6. Trigger alert if flood conditions are met  
7. Send SMS notification via GSM module  
8. Update system status  

## Project Structure
iot-flood-monitoring-system/  
├── arduino/        # Arduino code for sensor handling  
├── esp/            # ESP communication logic  
├── gsm/            # GSM module (SMS functionality)  
├── diagrams/       # System diagrams and flowcharts  
│   ├── flowchart.png  
│   └── system_diagram.png  
└── README.md  

## Technologies Used
- C/C++ (Arduino)  
- Embedded Systems Design  
- IoT Communication Protocols  
- GSM (A9G module)  
- Ultrasonic Sensor Integration  

## Setup and Installation
Hardware Requirements:
- Arduino-compatible microcontroller  
- Ultrasonic sensor  
- ESP module  
- GSM A9G module  
- Power supply  

Software Requirements:
- Arduino IDE  
- Serial Monitor  



## Results and Output
The system provides continuous water level readings, evaluates risk based on predefined thresholds and weather data, and triggers SMS alerts during high-risk flood conditions.

## Future Improvements
- Cloud integration for data logging and analytics  
- Web or mobile dashboard for monitoring  
- Machine learning-based flood prediction  
- GPS integration for location-based alerts  

## Applications
- Flood early warning systems  
- Environmental monitoring  
- Smart city infrastructure  
- Disaster risk management  

## Author
Sam Clinton Ogoti 

