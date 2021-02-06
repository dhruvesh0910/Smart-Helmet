//First Module

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);//tx=10, rx=11

/* Motion Sensor */
/*int led = 13;                // the pin that the LED is atteched to
int sensor = 2;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

/* MQ-3 Alcohol Sensor Circuit with Arduino */
int sensorValue;
char state;
/*const int AOUTpin=0;//the AOUT pin of the alcohol sensor goes into analog pin A0 of the arduino
const int DOUTpin=2;//the DOUT pin of the alcohol sensor goes into digital pin D8 of the arduino
const int ledPin=13;//the anode of the LED connects to digital pin D13 of the arduino

int limit=LOW;
int value;
*/

void setup() {
  /* MQ-3 Alcohol Sensor Circuit with Arduino */
  BTSerial.begin(9600);
  Serial.begin(9600);//sets the baud rate
 //Serial.begin(9600);
 
  /*Motion Sensor*/
 /* pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  //Serial.begin(9600);        // initialize serial
  
  /*IR Sensor*/
  pinMode(A0,INPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  //pinMode(13,OUTPUT);
  digitalWrite(A2,HIGH);
  digitalWrite(A1,LOW);
}

void loop(){


  /*IR Sensor*/
  Serial.print("IR Sensor : ");
  Serial.println(analogRead(A0));
  delay(1000);
  if(analogRead(A0) > 250)
  {
    /* Alcohol Sensor */
    sensorValue = analogRead(4);
  Serial.print("MQ135 Alcohol Sensor : ");
  Serial.println(sensorValue);// read analog input pin 0
  //delay(1000);
  if(sensorValue>280 )//280 analog value= 300ppm which id gov. defind limit
  {
    //digitalWrite(13,LOW);
    BTSerial.write('n');
  Serial.println("alcohol");
    Serial.println("OFF ");
  }
  else
  {
    //digitalWrite(13,HIGH);
    BTSerial.write('y');
  Serial.println("notalcohol");
    Serial.println("ON ");
  }
  //Serial.println(sensorValue, DEC);  // prints the value read
  delay(100);                        // wait 100ms for next reading
  //digitalWrite(13,HIGH);
  //delay(100);
  }
  else
  {
  //digitalWrite(13,LOW);
  BTSerial.write('n');
  Serial.println("helmet");
  delay(100);
  }
  
  /* MQ-3 Alcohol Sensor Circuit with Arduino */
  /*sensorValue = analogRead(0);
  Serial.println(sensorValue);// read analog input pin 0
  if(sensorValue>200)
  {
    digitalWrite(13,HIGH);
  }
  else
  {
    digitalWrite(13,LOW);
  }
  //Serial.println(sensorValue, DEC);  // prints the value read
  delay(100);                        // wait 100ms for next reading
  
  /*Motion Sensor*/
  /*val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
    delay(100);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      digitalWrite(led, LOW); // turn LED OFF
      delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }*/
  
}
