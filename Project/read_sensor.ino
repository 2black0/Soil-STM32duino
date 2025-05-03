// library used
#include <Battery.h>
#include <SimpleDHT.h>
#include <DallasTemperature.h>

// pin configuration
#define BAT_PIN PA0
#define SOIL_PIN PA1
#define ONE_WIRE_BUS PB12
#define DHT_PIN PB14

// dht22 configuration
SimpleDHT22 dht22(DHT_PIN);

// ds18b20 configuration
OneWire  ds(ONE_WIRE_BUS);
DallasTemperature sensors(&ds);

// battery configuration
Battery battery(3000, 4200, BAT_PIN);

void setup() {
  Serial.begin(115200);
  delay(100);
  battery.begin(3300, 0.4983);
}

void loop() {
  Serial.println("Read All Sensor");
  
  // Read DHT22
  float air_temp = 0;
  float air_hum = 0;
  int err = SimpleDHTErrSuccess;
  
  if ((err = dht22.read2(&air_temp, &air_hum, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err=");
    Serial.println(err);
    delay(100);
    //return;
  }
  Serial.print("Air Temp = ");Serial.print(air_temp); Serial.println(" C");
  Serial.print("Air Hum = ");Serial.print(air_hum); Serial.println(" %");

  // Read ds18b20
  sensors.requestTemperatures();
  int soil_temp = sensors.getTempCByIndex(0);
  if (soil_temp == -127.00){
    Serial.println("Read DS18B20 failed");
    delay(100);
    //return;
  }
  Serial.print("Soil Temp = ");Serial.print(soil_temp); Serial.println(" C");
  
  // Read Soil Moisture
  int soil_mois = 0;
  for (int i=0; i<10; i++){
    soil_mois = analogRead(SOIL_PIN);
    delay(10); 
  }
  soil_mois = soil_mois / 10;
  soil_mois = map(soil_mois,388,208,0,100);
  if(soil_mois>=100){soil_mois=100;}
  if(soil_mois<=0){soil_mois=0;}
  
  Serial.print("Soil Mois = ");Serial.print(soil_mois); Serial.println(" %");
  
  // Read Battery
  Serial.print("Battery Volt = ");Serial.print((float)battery.voltage()/1000);Serial.println(" V");
  Serial.print("Battery Level = ");Serial.print(battery.level());Serial.println(" %");

  // Delay
  Serial.println("-----------------------------------");
  delay(5000);
}
