ESP32 Temperature Monitoring with MCP9600
Overview

This project is a temperature monitoring system using an ESP32 and MCP9600 thermocouple sensor.
It demonstrates embedded firmware skills such as sensor interfacing (I2C), peripheral control (LEDs, buzzer), real-time task management with FreeRTOS, and clean modular code structure.

The system performs the following functions:

Reads temperature from MCP9600 sensor

Displays status via RGB LEDs (green = normal, red = alarm)

Triggers buzzer alerts when temperature exceeds a threshold

Uses non-blocking loops and FreeRTOS tasks for timing and reliability

Features
Feature	Description
MCU	ESP32
Sensor	MCP9600 (thermocouple) via I2C
Visual Alerts	RGB LED: Green = normal, Red = alarm (blinking)
Audio Alerts	Buzzer activated on alarm
Real-Time OS	FreeRTOS task scheduling for normal/alarm loops
Error Handling	Logs errors when temperature read fails or sensor not detected
Modular Code	Drivers for sensor, LED, and buzzer in separate files
Adjustable Threshold	Alarm temperature configurable via variable.c
Folder Structure
ESP32_Temp_Project/
├── main.c              # Main application loop
├── temp.c / temp.h     # MCP9600 sensor driver
├── buzzer.c / buzzer.h # Buzzer control
├── led.c / led.h       # RGB LED control
├── variable.c          # Global variables and thresholds
├── README.md           # Project documentation


Code Organization Principles

Each peripheral has its own driver module

main.c contains only the application loop and high-level logic

Non-blocking, real-time-friendly design with FreeRTOS delays

Logging using ESP_LOG for monitoring and debugging

Hardware Connections

MCP9600 → I2C (SDA, SCL pins on ESP32)

RGB LED → GPIO pins for Red, Green, Blue

Buzzer → GPIO configured for digital output
