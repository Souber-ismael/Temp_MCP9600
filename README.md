ESP32 Temperature Monitoring with MCP9600

A modular embedded firmware project using ESP32 to monitor temperature with the MCP9600 thermocouple sensor.
Demonstrates sensor interfacing, peripheral control, FreeRTOS, and clean firmware architecture.

🌟 Features

MCU: ESP32

Sensor: MCP9600 (I2C thermocouple)

Visual Alerts: RGB LED (Green = normal, Red = alarm)

Audio Alerts: Buzzer activated on alarm

Real-Time OS: FreeRTOS tasks for timing

Error Handling: Logs for sensor errors or missing devices

Modular Drivers: Separate files for sensor, LED, and buzzer

Configurable Threshold: Alarm temperature set in variable.c



Design Principles:

Each peripheral has its own driver module

main.c contains application logic only

Non-blocking FreeRTOS-based loops

Logging with ESP_LOG for debugging
