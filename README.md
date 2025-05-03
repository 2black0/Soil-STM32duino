# 🌱 Soil Monitoring System using STM32 and SIM800L

This project is a **remote soil monitoring system** powered by an STM32 microcontroller and SIM800L module, designed to measure and report multiple environmental parameters via GSM/GPRS to [ThingSpeak](https://thingspeak.com/). It’s suitable for agricultural IoT applications with solar-powered operation and future scalability.

---

## 🧰 Hardware Components

* **STM32F103C8T6 (Bluepill)** – Main microcontroller
* **SIM800L** – GSM/GPRS communication module
* **Soil Moisture Sensor** – Analog soil humidity sensor
* **DHT22** – Air temperature and humidity sensor
* **DS18B20** – Waterproof soil temperature sensor (1-Wire)
* **Relay Module** – Controls water pump
* **Solar Cell (5V output)** – Renewable power source
* **3x 18650 Li-ion Batteries (Parallel)** – Rechargeable power backup
* **Auto Charging Module (1S)** – Solar charge controller

---

## ✨ Features

* 🌡️ Measure air temperature & humidity (DHT22)
* 🌱 Monitor soil moisture & temperature (Soil Sensor + DS18B20)
* 🔋 Monitor battery voltage via ADC (PA0)
* 📡 Upload data to ThingSpeak via SIM800L (HTTP POST)
* 🌞 Operates on solar energy, energy-efficient with sleep routines
* 💧 Water pump control via relay (future development)
* 🤖 Future upgrade: Telegram bot notifications

---

## 📂 File Overview

| File                   | Description                                                                 |
| ---------------------- | --------------------------------------------------------------------------- |
| `full_code.ino`        | Complete integrated code for the entire monitoring and communication system |
| `read_sensor.ino`      | Standalone code for testing and reading each sensor module                  |
| `sleep_thingspeak.ino` | SIM800 HTTP routine with sleep control using STM32’s internal RTC           |

> 💡 Note: Sleep functionality will not activate when USB is connected. Use battery/serial power during deployment.

---

## 🛰️ Data Visualization

Data is sent to **ThingSpeak** in a single HTTP POST request, updating:

1. Air Temperature (DHT22)
2. Air Humidity (DHT22)
3. Soil Temperature (DS18B20)
4. Soil Moisture
5. Battery Voltage
6. Pump Status (Future)

---

## 🔧 Pin Configuration Summary

| Sensor / Module       | Pin (STM32)  |
| --------------------- | ------------ |
| DHT22 (Air Temp/Hum)  | PB14         |
| DS18B20 (Soil Temp)   | PB12         |
| Soil Moisture Sensor  | PA1          |
| Battery Voltage (ADC) | PA0          |
| SIM800L (GSM UART)    | Serial1      |
| Relay (Pump Control)  | Customizable |

---

## 🚀 Getting Started

### 1. Clone This Repository

```bash
git clone https://github.com/2black0/Soil-Monitoring-System.git
```

### 2. Flash the Firmware

Use **Arduino IDE** with **STM32duino** core or **PlatformIO** to flash `full_code.ino` to your Bluepill.

### 3. Power Supply Setup

* Ensure your solar cell outputs a stable 5V
* Use proper protection circuitry for Li-ion cells

---

## 📌 Roadmap

* [x] Send data to ThingSpeak via SIM800L
* [x] Use deep sleep for power saving
* [ ] Activate pump under low soil moisture or high temp
* [ ] Add Telegram bot for real-time alerts

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---