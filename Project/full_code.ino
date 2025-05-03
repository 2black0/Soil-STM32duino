// library used
#include <STM32Sleep.h>
#include <RTClock.h>
#include <Battery.h>
#include <SimpleDHT.h>
#include <DallasTemperature.h>

// pin configuration
#define BAT_PIN PA0
#define SOIL_PIN PA1
#define ONE_WIRE_BUS PB12
#define DHT_PIN PB14
#define led_pin PC13

// dht22 configuration
SimpleDHT22 dht22(DHT_PIN);

// ds18b20 configuration
OneWire  ds(ONE_WIRE_BUS);
DallasTemperature sensors(&ds);

// battery configuration
Battery battery(3000, 4200, BAT_PIN);

// sleep and rtc configuration
RTClock rt(RTCSEL_LSE);
long int alarmDelay = 3000;

// thingspeak configuration
String api_key = "T8BYFAE4ISGJ5WKG";

// data variable used
float data1, data2, data5;
int data3, data4, data6;

void setup(){
  //Serial.begin(115200);
  Serial1.begin(9600);
  delay(1000);
  digitalWrite(led_pin, HIGH);
  delay(1000);
  digitalWrite(led_pin, LOW);
  delay(1000);
  battery.begin(3300, 0.4983);
  //Serial.println("Start");
  //Serial.println("--------------------");
  delay(100);   
  read_sensor();
  delay(100);       
  Send2Pachube();
   
  //ShowSerialData();
  //Serial.println("--------------------");
  //Serial.println("Sleep");
  sleepAndWakeUp(STANDBY, &rt, alarmDelay);
}
 
void loop(){
}

void read_sensor(){
  //Serial.println("Read All Sensor");
  
  // Read DHT22
  float air_temp = 0;
  float air_hum = 0;
  int err = SimpleDHTErrSuccess;
  
  if ((err = dht22.read2(&air_temp, &air_hum, NULL)) != SimpleDHTErrSuccess) {
    //Serial.print("Read DHT22 failed, err=");
    //Serial.println(err);
    delay(100);
    return;
  }
  //Serial.print("Air Temp = ");Serial.print(air_temp); Serial.println(" C");
  //Serial.print("Air Hum = ");Serial.print(air_hum); Serial.println(" %");

  // Read ds18b20
  sensors.requestTemperatures();
  int soil_temp = sensors.getTempCByIndex(0);
  if (soil_temp == -127.00){
    //Serial.println("Read DS18B20 failed");
    delay(100);
    return;
  }
  //Serial.print("Soil Temp = ");Serial.print(soil_temp); Serial.println(" C");
  
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
  
  //Serial.print("Soil Mois = ");Serial.print(soil_mois); Serial.println(" %");
  
  // Read Battery
  //Serial.print("Battery Volt = ");Serial.print(battery.voltage());Serial.println(" V");
  //Serial.print("Battery Level = ");Serial.print(battery.level());Serial.println(" %");
  data1 = air_temp;
  data2 = air_hum;
  data3 = soil_temp;
  data4 = soil_mois;
  data5 = (float)battery.voltage()/1000;
  data6 = battery.level();
}

void Send2Pachube(){
  Serial1.println("AT");
  delay(1000);

  Serial1.println("AT+CPIN?");
  delay(1000);

  Serial1.println("AT+CREG?");
  delay(1000);

  Serial1.println("AT+CGATT?");
  delay(1000);

  Serial1.println("AT+CIPSHUT");
  delay(1000);

  Serial1.println("AT+CIPSTATUS");
  delay(2000);

  Serial1.println("AT+CIPMUX=0");
  delay(2000);
  //ShowSerialData();
 
  Serial1.println("AT+CSTT=\"3gprs\"");//start task and setting the APN,
  delay(1000);
  //ShowSerialData();
 
  Serial1.println("AT+CIICR");//bring up wireless connection
  delay(3000);
  //ShowSerialData();
 
  Serial1.println("AT+CIFSR");//get local IP adress
  delay(2000);
  //ShowSerialData();
 
  Serial1.println("AT+CIPSPRT=0");
  delay(3000);
  //ShowSerialData();
  
  Serial1.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
  //ShowSerialData();
 
  Serial1.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  //ShowSerialData();
  
  String str="GET http://api.thingspeak.com/update?api_key=" + String(api_key) + "&field1=" + String(data1) + "&field2=" + String(data2) + "&field3="+ String(data3) + "&field4=" + String(data4) + "&field5=" + String(data5) + "&field6=" + String(data6);
  Serial1.println(str);//begin send data to remote server
  delay(4000);
  //ShowSerialData();

  Serial1.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  Serial1.println();
  //ShowSerialData();
 
  Serial1.println("AT+CIPSHUT");//close the connection
  delay(100);
  //ShowSerialData();
} 

/*void ShowSerialData()
{
  while(Serial1.available()!=0)
    Serial.write(Serial1.read());
}*/
