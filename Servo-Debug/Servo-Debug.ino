#include <Servo.h>

#define panPin 5
#define tiltPin 3

#define buttonPin 7

Servo pan;
Servo tilt;

String str;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pan.attach(panPin);
  tilt.attach(tiltPin);
  pinMode(buttonPin, INPUT); 

  pan.write(90);  
   delay(1000);
   tilt.write(90);
   delay(1000);
   Serial.println("DEBUG SERVO");
    
    
}

void loop() {
 
 // 
 if(Serial.available() > 0) {

  str = Serial.readStringUntil('\n');  
  Serial.println("I GOT "+str);
  str.trim();
 }  
  
 // if(digitalRead(buttonPin)) {  
 if ( str.equals("yoqsetio")) {
  
  // put your main code here, to run repeatedly:
  Serial.println("SERVO LOOP");
   pan.write(0);  
   delay(1000);
   tilt.write(0);
   delay(1000);

   pan.write(45);  
   delay(1000);
   tilt.write(45);
   delay(1000);

   pan.write(90);  
   delay(1000);
   tilt.write(90);
   delay(1000);

   pan.write(135);  
   delay(1000);
   tilt.write(135);
   delay(1000);

   pan.write(180);  
   delay(1000);
   tilt.write(180);
   delay(1000);
 }   
}
