# Soil Monitoring System

## Peripheral :
```
> STM32duino (bluepill)
> Sim800L (GSM / GPRS)
> Soil Moisture Sensor
> DHT11 (Air Temperature & Humidity Sensor)
> ds18b20 (Soil Temperature)
> Solar Cell (Output 5V)
> 3x 18650 Battery with Auto Charging for Solar Cell
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
