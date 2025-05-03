// send 6 random data to thingspeak
// sleep active every alarmDelay in seconds

#include <STM32Sleep.h>
#include <RTClock.h>

#define led_pin PC13

RTClock rt(RTCSEL_LSE);
long int alarmDelay = 20;

int data1, data2, data3, data4, data5, data6;
String api_key = "T8BYFAE4ISGJ5WKG";

void setup(){
  // serial com setup
  Serial.begin(115200);
  Serial1.begin(9600);
  delay(1000);
  digitalWrite(led_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(3000);              // wait for a second
  digitalWrite(led_pin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 
  //Serial.println("Start");
  //Serial.println("--------------------");
  data1=random(0,100);
  data2=random(0,100);
  data3=random(0,100);
  data4=random(0,100);
  data5=random(0,15);
  data6=random(0,100);
  delay(100);          
  Send2Pachube();
   
  //ShowSerialData();
  //Serial.println("--------------------");
  //Serial.println("Sleep");
  sleepAndWakeUp(STANDBY, &rt, alarmDelay);
}
 
void loop(){
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
