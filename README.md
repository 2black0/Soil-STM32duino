# Soil Monitoring System
## Peripheral :
```
> STM32duino (bluepill)
> Sim800L (GSM / GPRS)
> Soil Moisture Sensor
> DHT22 (Air Temperature & Humidity Sensor)
> DS18B20 (Soil Temperature)
> Solar Cell (Output 5V)
> 3x Parallel 18650 Battery
> Auto Charging Board 1S
> Relay for Water Pump
```
## Feature :
```
> All sensor can monitored in Thingspeak and Website
> Next : will add telegram bot notification if Pump Running
> Pump will run in a routine or A not good condition (temperature too HIGH or humidity too low)
```
## Note for file
### sleep_thingspeak.ino
```
> Apply sleep function in every routine based on internal RTC of STM32
> Send Multiple data (6 variables) with random value to thingspeak server
```
### read_sensor.ino
```
> Read Sensor DHT22 : pin PB14
> Read Sensor DS18B20 : pin PB12
> Read Battery Voltage : pin PA0 (note : battery max voltage is 4.2v)
> Read Soil Mois Sensor : pin PA1
```
