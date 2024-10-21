#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Servo myservo;
int pos = 0;
boolean fire = false;
double temp;
#define Left 10 // left sensor
#define Right 8 // right sensor
#define Forward 9 // front sensor
#define LM1 2 // left motor
#define LM2 3 // left motor
#define RM1 5 // right motor
#define RM2 4 // right motor
#define pump 6
void setup() {
Serial.begin(9600); 
 pinMode(Left, INPUT);
 pinMode(Right, INPUT);
 pinMode(Forward, INPUT);pinMode(LM1, OUTPUT); 
 pinMode(LM2, OUTPUT);
 pinMode(RM1, OUTPUT);
 pinMode(RM2, OUTPUT);
 pinMode(pump, OUTPUT);
 digitalWrite(pump, HIGH);
 mlx.begin();
 myservo.attach(11);
 myservo.write(90);
 delay(500);
}
void put_off_fire() {
 delay(1000);
 digitalWrite(LM1, LOW);
 digitalWrite(LM2, LOW);
 digitalWrite(RM1, LOW);
 digitalWrite(RM2, LOW);
 digitalWrite(pump, LOW);
 Serial.println("Pump: ON");
 delay(500);
 for (pos = 50; pos <= 130; pos += 1) {
 myservo.write(pos);
 delay(10);
 }
 for (pos = 130; pos >= 50; pos -= 1) {
 myservo.write(pos);
 delay(10);
 }
 digitalWrite(pump, HIGH);
 Serial.println("Pump: OFF");
 delay(1500);
 myservo.write(90);
 delay(1000);
 fire = false;
}
void loop() {
 temp = mlx.readObjectTempC();
 myservo.write(90);
 delay(250);
 Serial.print("Temperature: ");
 Serial.print(temp);
 Serial.println(" °C");
 Serial.print("Left Sensor: ");
 Serial.println(digitalRead(Left));
 Serial.print("Right Sensor: ");
Serial.println(digitalRead(Right));
 Serial.print("Forward Sensor: ");
 Serial.println(digitalRead(Forward));
 if (digitalRead(Left) == 1 && digitalRead(Right) == 1 && digitalRead(Forward) == 1) {
 digitalWrite(LM1, LOW);
 digitalWrite(LM2, LOW);
 digitalWrite(RM1, LOW);
 digitalWrite(RM2, LOW);
 Serial.println("All Sensors: HIGH - Motors: LOW");
 } else if (digitalRead(Forward) == 0) {
 digitalWrite(LM1, HIGH);
 digitalWrite(LM2, LOW);
 digitalWrite(RM1, HIGH);
 digitalWrite(RM2, LOW);
 Serial.println("Forward Sensor: LOW - Moving Forward");
 } else if (digitalRead(Left) == 0) {
 digitalWrite(LM1, HIGH);
 digitalWrite(LM2, LOW);
 digitalWrite(RM1, LOW);
 digitalWrite(RM2, HIGH);
 Serial.println("Left Sensor: LOW - Turning Left");
 } else if (digitalRead(Right) == 0) {
 digitalWrite(LM1, LOW);
 digitalWrite(LM2, HIGH);
 digitalWrite(RM1, HIGH);
 digitalWrite(RM2, LOW);


 Serial.println("Right Sensor: LOW - Turning Right");
 }
 if (temp > 25) {
 put_off_fire();
 } else {
 fire = false;
 delay(1000);
 } // Adjust delay time as needed for monitoring
}