#include "TinyGPS++.h"
#include<SoftwareSerial.h>
SoftwareSerial serial_connection(10, 11); //RX=pin 11, TX=pin 10 GPS
SoftwareSerial BTSerial(2, 3);//tx=2,rx=3
//SoftwareSerial GSMSerial(4, 5);//tx=4,rx=5
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data
SoftwareSerial mySerial(4, 5);
char msg;
char call;

// defines pins numbers
const int trigPin = 8;
const int echoPin = 9;
// defines variables
long duration;
int distance,sendsms=0;
int btflag=0;
float lati,lon,latii,longi;
char state;


void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(12,OUTPUT); // relay

digitalWrite(7,HIGH);//reset
pinMode(7,OUTPUT);//reset

//GSMSerial.begin(9600);
 mySerial.begin(9600); 
serial_connection.begin(9600);//This opens up communications to the GPS
BTSerial.begin(38400);
Serial.begin(9600); // Starts the serial communication

delay(300);

/*
//Serial.println("AT+CREG=1,0");
Serial.println("AT+CMGF=1");    
delay(2000);
Serial.print("AT+CMGS=\"8733979533\"\r");
//Serial.print(phone_no); 
Serial.write(0x22);
Serial.write(0x0D);  // hex equivalent of Carraige return    
Serial.write(0x0A);  // hex equivalent of newline
delay(2000);
Serial.print("Welcome in Smart Helmet");
delay(100);
Serial.println (char(26));//the ASCII code of the ctrl+z is 26
//BTSerial.begin(9600);*/
}



int sms()
{
 // serial_connection.listen();//This opens up communications to the GPS
  serial_connection.begin(9600);
  serial_connection.listen();
  for(;;){

 while(serial_connection.available())//While there are characters to come from the GPS
  {
    //Serial.println(gps.location.isUpdated());
    gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
  }
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    //Serial.println("2");
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
    //Serial.begin(9600);
    Serial.println("Satellite Count:");
    Serial.println(gps.satellites.value());
    Serial.println("Latitude:");
    Serial.println(latii=gps.location.lat(), 6);
    Serial.println("Longitude:");
    Serial.println(longi=gps.location.lng(), 6);
    Serial.println("Speed MPH:");
    Serial.println(gps.speed.mph());
    Serial.println("Altitude Feet:");
    Serial.println(gps.altitude.feet());
    Serial.println("");
  }
  if(latii!=0.00){
    
    break;
    }
  }
  serial_connection.end();
  

//Serial.begin(9600);  
//Serial.listen();
//Serial.println("AT+CREG=1,0");   
  Serial.print("message");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918733979533\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.print("http://maps.google.com/?q=");
  mySerial.print(latii,6);
  mySerial.print(",");
  mySerial.print(longi,6);// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
   Serial.print("complete");
  delay(1000);
  digitalWrite(12,HIGH);
 delay(2000);
  digitalWrite(7,LOW);//reset
 return 1;
//  break;
//BTSerial.listen();
}


void loop() {
 
  //BTSerial.begin(9600);
if(BTSerial.available() > 0)
 { 
  
    // Checks whether data is comming from the serial port
    state = BTSerial.read(); // Reads the data from the serial port
    //Serial.println(state); 
//  Serial.listen();
    if(state=='y')
    {
      Serial.println("start");
digitalWrite(12,LOW);

// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2; //cm distance 1
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
if(distance<20)
{
  if(sendsms==0)
  {
   // BTSerial.end();
     int i = sms(); 
  // break;
    //Serial.print("Ayi gayu");
    sendsms=1;
     Serial.begin(9600);
  BTSerial.begin(9600);
  }
}
else
{
  sendsms=0;
}
delay(1000);  
    }
    if(state=='n'){
      Serial.println("stop");
      digitalWrite(12,HIGH);
    }
 }
// Serial.end();

}
