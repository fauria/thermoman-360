#include <Servo.h>
#include <math.h>

#define panPin 5
#define tiltPin 3
#define panErr 0
#define tiltErr 0

#define cameraFOVx 53.50
#define cameraFOVy 41.41

#define sensorFOVx 10
#define sensorFOVy 10

Servo pan, tilt;

int start[] = { round((180-ceil(cameraFOVx))/2), round((180-ceil(cameraFOVy))/2) }; 
int scan[] = { ceil(cameraFOVx/sensorFOVx), ceil(cameraFOVy/sensorFOVy) };

void setup() {

  // x: 0: pan, y: 1: tilt
  
  Serial.begin(9600);
  pan.attach(panPin);
  tilt.attach(tiltPin);

  pan.write(start[0]+panErr);  
  tilt.write(start[1]+tiltErr);

  pinMode(7, INPUT); 
}

void loop() { 
  pan.write(start[0]+panErr);  
  tilt.write(start[1]+tiltErr);
  if(digitalRead(7)){
    //Serial.println("BEGIN");  
    for(int i = start[1]; i <= start[1]+ceil(cameraFOVy); i+=scan[1]*2) {
      //Serial.println(i);
      tilt.write(i+tiltErr);    
      delay(50);
      for(int j = start[0]; j <= start[0]+ceil(cameraFOVx); j+=scan[0]*2) {
        //Serial.println(j);
        pan.write(j+panErr);
        delay(150);
      }
    }
  }
  
  
  
    
  //Serial.println("END");  
 
  
  
}

