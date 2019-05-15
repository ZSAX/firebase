#include <WiFi.h>
#include "FirebaseESP32.h"
#include <ESP32_Servo.h>
#include "DHT.h"

#define FIREBASE_HOST "sg001-353df.firebaseio.com" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xmB7sKI2O7J9XJeqsZYkpw3HzeIG5poF0UvUycDc"
#define WIFI_SSID "qwq"
#define WIFI_PASSWORD "0908113563"

#define DHTPIN 25     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

Servo myservo1;
Servo myservo2;
Servo myservo3;

DHT dht(DHTPIN, DHTTYPE);

FirebaseData firebaseData;

int servoPin1 = 18;
int servoPin2 = 19;
int servoPin3 = 23;

String m1="OFF";
String m2="OFF";
String m3="OFF";

int waters=33;

int sensorPin1=36;
int sensorPin2=39;
int sensorPin3=34;
int sensorPin4=35;
int sensorPin5=32;

int LED1=12;
int LED2=14;
int LED3=27;

unsigned long sendDataPrevMillis = 0;
String path0 = "/ESP32_Test";
String path1 = "/ESP32_motor";
uint16_t count = 0;
void setup()
{ 
  myservo1.attach(servoPin1);
  myservo1.write(0); 
  myservo2.attach(servoPin2);
  myservo2.write(0); 
  myservo3.attach(servoPin3);
  myservo3.write(0); 
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  
  dht.begin();
   
  pinMode(sensorPin1,INPUT);
  pinMode(sensorPin2,INPUT);
  pinMode(sensorPin3,INPUT);
  pinMode(sensorPin4,INPUT);
  pinMode(sensorPin5,INPUT);

  pinMode(waters,INPUT);
  
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  Serial.println("------------------------------------");
  Serial.println("Begin stream connection...");

    if (Firebase.setString(firebaseData, path1 + "/water/motor1", m1 ))
    {    }
    if (Firebase.setString(firebaseData, path1 + "/water/motor2", m2 ))
    {    }
    if (Firebase.setString(firebaseData, path1 + "/water/motor3", m3 ))
    {    }
  
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();   
  float moist1 = analogRead(sensorPin1);
  float moist2 = analogRead(sensorPin2);
  float moist3 = analogRead(sensorPin3);
  float moist4 = analogRead(sensorPin4);
  float moist5 = analogRead(sensorPin5);
  float water  = analogRead(waters);
  if (millis() - sendDataPrevMillis >5000)
  {
    sendDataPrevMillis = millis();
    count++;

    Serial.println("------------------------------------");
    Serial.println("Set string...");

    if (Firebase.setString(firebaseData, path0 + "/Stream/dth/temperature", t + String(count)))
    {    }
    if (Firebase.setString(firebaseData, path0 + "/Stream/dth/Humidity", h + String(count)))
    {    }
    if (Firebase.setString(firebaseData, path0 + "/Stream/soil/soil1", moist1 + String(count)))
    {    }
    if (Firebase.setString(firebaseData, path0 + "/Stream/soil/soil2", moist2 + String(count)))
    {    }
    if (Firebase.setString(firebaseData, path0 + "/Stream/soil/soil3", moist3 + String(count)))
    {    }
    if (Firebase.setString(firebaseData, path0 + "/Stream/soil/soil4", moist4 + String(count)))
    {    }
    if (Firebase.setString(firebaseData, path0 + "/Stream/soil/soil5", moist5 + String(count)))
    {    }
    if (Firebase.setString(firebaseData, path0 + "/Stream/water sensor/water", water + String(count)))
    {    }
   
    if (Firebase.getString(firebaseData, path1 + "/water/motor1"))
    {
      Serial.println("----------M1-----------");
      if (firebaseData.dataType() == "string")
      Serial.println(firebaseData.stringData());
      m1=firebaseData.stringData();
      //Serial.println(m1);
    }
    if (Firebase.getString(firebaseData, path1 + "/water/motor2"))
    {
      Serial.println("----------M2-----------");
      if (firebaseData.dataType() == "string")
      Serial.println(firebaseData.stringData());
      m2=firebaseData.stringData();
      //Serial.println(m2);
    }
    if (Firebase.getString(firebaseData, path1 + "/water/motor3"))
    {
      Serial.println("----------M3-----------");
      if (firebaseData.dataType() == "string")
      Serial.println(firebaseData.stringData());
      m3=firebaseData.stringData();
      //Serial.println(m3);
    }
//----------------------------------------------------------led

if(m1=="ON")
{ digitalWrite(LED1, HIGH);}
else
{ digitalWrite(LED1, LOW);}
/*
if(m2=="ON")
{ digitalWrite(LED2, HIGH);}
else
{ digitalWrite(LED2, LOW);}
if(m3=="ON")
{ digitalWrite(LED3, HIGH);}
else
{ digitalWrite(LED3, LOW);}
*/
//----------------------------------------------------------soil 

if(moist1>=2500)
{m1="ON";}
else
{m1="OFF";}
/*
if(moist2>=2500)
{m1="ON";}
else
{m1="OFF";}

if(moist3>=2500)
{m1="ON";}
else
{m1="OFF";}
//--------------
if(moist4>=2500)
{m2="ON";}
else
{m1="OFF";}

if(moist5>=2500)
{m2="ON";}
else
{m1="OFF";}
*/
//----------------------------------------------------------------water 
/*
if(water<=30)
{m3="ON";}
if(water>=70)
{m3="OFF";}
*/
//----------------------------------------------------------------motor control
if(m1=="ON")
{myservo1.write(180); }
else
{myservo1.write(0); }
if(m2=="ON")
{myservo2.write(180); }
else
{myservo2.write(0); }
if(m3=="ON")
{myservo3.write(180); }
else
{myservo3.write(0); }
//----------------------------------------------------------------SET 
    if (Firebase.setString(firebaseData, path1 + "/water/motor1", m1 ))
    {    }
    if (Firebase.setString(firebaseData, path1 + "/water/motor2", m2 ))
    {    }
    if (Firebase.setString(firebaseData, path1 + "/water/motor3", m3 ))
    {    }

  }
   
}
