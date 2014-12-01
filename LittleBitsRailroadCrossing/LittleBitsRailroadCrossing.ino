/*

Arduino+LittleBits code for a railroad crossing. Uses LED + Light Sensor bits
to detect the approaching train. Wired up to an Arduino bit. The Arduino has
two LED bits and Servo bit for outputs.

The Arduino outputs the value of the light sensor bit to the
Serial monitor for debugging.

*/

const int LED_PIN1 = 1;
const int LED_PIN2 = 5;
const int SERVO_PIN = 9;
const int SENSOR_PIN = A1;

const int BLINK_TIMES = 5;
const int BLINK_INTERVAL = 500;
const int LIGHT_THRESHOLD = 50;

void setup() {
  
  Serial.begin(9600);
  
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
}

void loop() {

  int lightSensorValue = analogRead(SENSOR_PIN);  
    
  Serial.print("Light = ");
  Serial.println(lightSensorValue);
  
  // When the train crosses, the light level should drop significantly
  boolean isTrainCrossing = lightSensorValue < LIGHT_THRESHOLD;
  
  if (isTrainCrossing) {
    
    Serial.println("Train crossing");
    
    // Turn on the servo to lower the gate
    digitalWrite(SERVO_PIN, HIGH);   
    
    for (int i = 0; i < BLINK_TIMES; i++) {
      
        // Blink first light
        digitalWrite(LED_PIN1, HIGH);
        digitalWrite(LED_PIN2, LOW);
        
        delay(BLINK_INTERVAL);
        
        // Blink second light
        digitalWrite(LED_PIN1, LOW);
        digitalWrite(LED_PIN2, HIGH);     
     
        delay(BLINK_INTERVAL);         
    }
    
    Serial.println("Done");
    
    // Turn everything off
    digitalWrite(LED_PIN1, LOW);
    digitalWrite(LED_PIN2, LOW);
    digitalWrite(SERVO_PIN, LOW);    
  }
  
  delay(200);
}
