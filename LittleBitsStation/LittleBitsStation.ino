/*

Arduino+LittleBits code for a Lego railroad station. Detects a
train crossing via light snesor, then stop the train via an IR
LED. It waits a couple seconds, then starts the train again.

Uses an existing Arduino library to control the Lego Power
Functions:

http://forum.arduino.cc/index.php?topic=89310.0

*/

#include <legopowerfunctions.h>

const int IR_PIN = 5;
const int SENSOR_PIN = A0;

const int LIGHT_THRESHOLD = 50;
const int TRAIN_SPEED = PWM_FWD3;
const int TRAIN_STOP_DELAY = 5000; // How long to stop the train for
const int TRAIN_PASS_DELAY = 3000; // How to long to wait till train clears

LEGOPowerFunctions lego(IR_PIN);

void setup() {
  
  Serial.begin(9600);
}

void loop() {
  
  int lightSensorValue = analogRead(SENSOR_PIN);
  
  Serial.print("Light = ");
  Serial.println(lightSensorValue);
  
  // When the train crosses, the light level should drop significantly
  boolean isTrainCrossing = lightSensorValue < LIGHT_THRESHOLD;
  
  if (isTrainCrossing) {
   
    Serial.println("Stop train");
    
    setTrainSpeed(PWM_FLT);
    
    delay(TRAIN_STOP_DELAY);
    
    setTrainSpeed(TRAIN_SPEED);
    
    Serial.println("Start train");
    
    delay(TRAIN_PASS_DELAY);
    
    Serial.println("Train cleared");
  }
}

void setTrainSpeed(int speed) {
  
  lego.SingleOutput(0, speed, RED, CH1);
}


