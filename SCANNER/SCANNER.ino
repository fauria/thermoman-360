#include <Servo.h>
#include <i2cmaster.h>
#include <math.h>

#define panPin 5
#define tiltPin 3

#define panErr 0
#define tiltErr 0

#define cameraFOVx 53.50
#define cameraFOVy 41.41

#define sensorFOVx 10
#define sensorFOVy 10

#define safeMargin 250

#define thermistor 3975

Servo pan;
Servo tilt;

String cmd;

int start[] = { round((180-ceil(cameraFOVx))/2), round((180-ceil(cameraFOVy))/2) }; 
int scan[] = { ceil(cameraFOVx/sensorFOVx), ceil(cameraFOVy/sensorFOVy) };

void setup() {
  
  Serial.begin(9600);
  i2c_init();
  PORTC = (1 << PORTC4) | (1 << PORTC5);
    
  pan.attach(panPin);
  tilt.attach(tiltPin);

  pan.write(start[0]+panErr);  
  tilt.write(start[1]+tiltErr);
  
  neutral();
}

void loop() {   
  if(Serial.available() > 0) {
    
    cmd = Serial.readStringUntil('\n');      
    cmd.trim();

    if ( cmd.equals("snap")) {      
      snap();  
    } else if ( cmd.equals("reset")) {
      reset();    
    } else if ( cmd.equals("neutral")) {    
      neutral();
    } else if ( cmd.equals("ambient")) {    
      ambient();                
    } else if ( cmd.equals("scan")) {
      reset();      
      Serial.println("begin-scan");      
      
      int row = 0;
      int column = 0;
      String json = "[[";

      for(int i = start[1]; i <= start[1]+ceil(cameraFOVy); i+=scan[1]*2) {
        
        tilt.write(i+tiltErr);    
        
        for(int j = start[0]; j <= start[0]+ceil(cameraFOVx); j+=scan[0]*2) {        
          pan.write(j+panErr);                  
          json += String(temp());
          json += ",";
          column++;
        }
        json.remove(json.length()-1, 1);
        json += "],[";
        column = 0;
        row++;
      }
      json.remove(json.length()-2, 2);
      json += "]";
      Serial.println(json);      
      Serial.println("end-scan");        
    }
    
  }    
}

void snap() {  
  pan.write(90);
  tilt.write(180);
  delay(safeMargin);
  Serial.println("ok-snap");    
}

void neutral() {  
  pan.write(90);
  tilt.write(90);  
  delay(safeMargin);
  Serial.println("ok-neutral");
}

void reset() { 
  pan.write(start[0]+panErr);  
  tilt.write(start[1]+tiltErr);  
  delay(safeMargin);
  Serial.println("ok-reset");  
}

float ambient() {
  Serial.println("begin-ambient");
  int a = analogRead(0);
  float resistance = (float)(1023-a)*10000/a;
  float temperature = 1/(log(resistance/10000)/thermistor+1/298.15)-273.15;  
  Serial.println(temperature);
  Serial.println("end-ambient");  
}

float temp() {

  //delay(500);
  //return 22.2;
  
  int dev = 0x5A<<1;
    int data_low = 0;
    int data_high = 0;
    int pec = 0;
    
    i2c_start_wait(dev+I2C_WRITE);
    i2c_write(0x07);
    
    // read
    i2c_rep_start(dev+I2C_READ);
    data_low = i2c_readAck(); //Read 1 byte and then send ack
    data_high = i2c_readAck(); //Read 1 byte and then send ack
    pec = i2c_readNak();
    i2c_stop();
    
    //This converts high and low bytes together and processes temperature, MSB is a error bit and is ignored for temps
    double tempFactor = 0.02; // 0.02 degrees per LSB (measurement resolution of the MLX90614)
    double tempData = 0x0000; // zero out the data
    int frac; // data past the decimal point
    
    // This masks off the error bit of the high byte, then moves it left 8 bits and adds the low byte.
    tempData = (double)(((data_high & 0x007F) << 8) + data_low);
    tempData = (tempData * tempFactor)-0.01;
    
    float celcius = tempData - 273.15;
    float fahrenheit = (celcius*1.8) + 32;

    delay(safeMargin);
    return celcius;
}

