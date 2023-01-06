#define BLYNK_TEMPLATE_ID "TMPLyGz-bsVx"
#define BLYNK_DEVICE_NAME "AGRICULTURE"
#define BLYNK_AUTH_TOKEN "Tk53sUD40uRFzsxhi2jfXzBjQCrCZ391"
#define BLYNK_PRINT Serial
#define motor D0
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "mi";
char pass[] = "Sharath@123";
const int AirValue = 620;   //you need to replace this value with Value_1
const int WaterValue = 310;  //you need to replace this value with Value_2
int soilMoistureValue = 0;
int soilmoisturepercent=0;
int sensor = A0;
BlynkTimer timer;
void myTimerEvent()
{
   Blynk.virtualWrite(V0,digitalRead(motor));
   Blynk.virtualWrite(V1,soilmoisturepercent);
}
void setup()
{
Serial.begin(9600); 



pinMode(motor,OUTPUT);
Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);

}
void loop()  {
  Blynk.run();
  timer.run();
soilMoistureValue = analogRead(sensor);  //put Sensor insert into soil
Serial.print("sensor value");
Serial.println(soilMoistureValue);
soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
if(soilmoisturepercent >= 100)
{
  Serial.print("moisture is ");
  Serial.println("100 %");
}
else if(soilmoisturepercent <=0)
{
  Serial.print("moisture is ");
  Serial.println("0 %");
}
else if(soilmoisturepercent >0 && soilmoisturepercent < 100)
{
  Serial.print("moisture is ");
  Serial.print(soilmoisturepercent);
  Serial.println("%");
  
}
if(soilmoisturepercent <= 30)
{
  digitalWrite(motor,LOW);
  Serial.println("MOTOR IS ONN");
  }
  if(soilmoisturepercent >= 80)
  {
    digitalWrite(motor,HIGH);
    Serial.println("MOTOR IS OFF");
  }
  delay(1000);
}