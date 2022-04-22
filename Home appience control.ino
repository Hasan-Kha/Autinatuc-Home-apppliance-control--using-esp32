#include <EEPROM.h>
#include "Wire.h"
#define DS3231_I2C_ADDRESS 0x68




//....................................Wifi
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "b8NMsOnAR1-USofWW3LTaRLlJxuaDKmi";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Ecoyva";
char pass[] = "ecoyvalab";

int AC_Relay = 15;
int temp = 33;

WidgetLED online(V1);
int AC;
int Time = 0;
int Time2 = 0;
const int R = 4; 
const int AC_pin = 5;                      // Relay 1 of BlynkBoard Conneted with D1(GPIO 05) pin of NodeMCU
// Relay 1 of BlynkBoard Conneted with D1(GPIO 05) pin of NodeMCU


BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(AC);
  Blynk.syncVirtual(Time);
}

BLYNK_WRITE(V3)
{
  AC = param.asInt();                            
  Blynk.virtualWrite(V3, AC);
}
//
//BLYNK_WR = param[V4].asLong();  // this would result in startTimeInSecs = 0
//   Time2 = param[V4].asLong();   // this would result in endTimeInSecs = 3600
//}

//BLYNK_WRITE(V4)
//{
//  Time = param.asInt();                            
//  Blynk.virtualWrite(V4, Time);
//}

//..............................................................

int hours = 0;   //Time
int minutes = 0;  //Time

int secondd = 0;
int minutee = 0;
int hourr = 0;

//...........................................................RTC
  byte decToBcd(byte val){
  return( (val/10*16) + (val%10) );
}
  byte bcdToDec(byte val){
  return( (val/16*10) + (val%16) );
}

void setup() {  
  Serial.begin(115200);

  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    pinMode(R,INPUT);
    pinMode(AC_pin,OUTPUT);
  }

  Serial.println("WiFi connected");  

  Blynk.begin(auth, ssid, pass);

}

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
  dayOfMonth, byte month, byte year){
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
void readDS3231time(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year){
  
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  secondd = *second = bcdToDec(Wire.read() & 0x7f);
  minutee = *minute = bcdToDec(Wire.read());
  hourr = *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());

  
// if(secondd != timerstate)
// {
//  if(secondd == secondd)
//  {
//    //........................pH
//    if(b == 1)
//    {
//    count4++;
//    }
//    if(count4 > 60)
//    {
//    count4 = 0;
//    }
//    
//    count5++;
//    if(count5 > 1)
//    {
//    count5 = 0;
//    }
//    //......................End
//    //......................Food
//    if(f == 1)
//    {
//    count6++;
//    }
//    if(count6 > 2)
//    {
//    count6 = 0;
//    }
//
//    if(g == 1)
//    {
//    count7++;
//    }
//    if(ii == 1)
//    {
//    count8++;
//    }
//
//    if(xx == 0)
//    {
//    count9++;
//    }
//    if(count9 == 3)
//    {
//    x = 1;
//    }
//
//    //..................................lcd.print
//    if(lcdprint == 1)
//    {
//    count11++;
//    }
//    if(count11 > 1)
//    {
//    count11 = 0;
//    }
//    }
//    }
//    timerstate = secondd;
 
}

void displayTime(){

  
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  Serial.print(hour);
  
  Serial.print(":");
  if (minute<10){
    Serial.print("0");
  }
  Serial.print(minute);
  Serial.print(":");
  if (second<10){
    Serial.print("0");
  }

//  if(mc == 0)
//  {
//  lcd.setCursor (6,0);
//  if(hourr < 10)
//  {
//  lcd.print ("0");
//  }
//  lcd.print (hourr);
//  lcd.print (":");
//  if(minutee < 10)
//  {
//  lcd.print ("0");
//  }
//  lcd.print (minutee);
//  lcd.print (":");
//  if(secondd < 10)
//  {
//  lcd.print ("0");
//  }
//  lcd.print (secondd);
//  lcd.print ("  ");

//  lcd.setCursor (5,1);
//  lcd.print (dayOfMonth);
//  lcd.print (".");
//  lcd.print (month);
//  lcd.print (".");
//  lcd.print (year);
//  lcd.print ("  ");
  //}
  
//  Serial.print(second);
//  Serial.print(" ");
//  Serial.print(dayOfMonth);
//  Serial.print("/");
//  Serial.print(month);
//  Serial.print("/");
//  Serial.print(year);
//  Serial.print("   ");
//  Serial.print ("count - ");
//  Serial.print(count);
//  Serial.println ("  ");
if(hourr > 24)
{
hourr = 1;
}
if(hourr < 1)
{
hourr = 24;
}
if(minutee > 59)
{
minutee = 0;
}
if(minutee < 0)
{
minutee = 59;
}
}

void loop(){

   displayTime();
    Blynk.run();
  online.on();
  Blynk.virtualWrite(V2, temp);
//  Blynk.virtualWrite(V2, T2);
//  Blynk.virtualWrite(V4, ph_act);
Serial.print ("v3 - ");
Serial.print (AC);
Serial.print ("  ");
Serial.print (Time);
Serial.print (":");
Serial.print (Time2);
if (digitalRead(R)==1)
{
  digitalWrite(AC_pin,HIGH);
  Serial.println("AC is on");
}
else
{
  Serial.println("AC off");
}
}
