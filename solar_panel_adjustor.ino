// Using Ultrasonic sensors as a replacement for LDR sesnors.
// Using distance of object as a replacement for sunlight strength. (Closer is Higher)
#include <Servo.h>
Servo Servo1; // Up-Down Controlling Servo
Servo Servo2; // Left-Right Controlling Servo
int degree_ud=0, degree_lr=0;
int range = 5, timeout = 20000; // Times out after 20s if it doesn't find an object (sun).

void setup()
{
  Servo1.attach(11);
  Servo2.attach(10);
  // Setting 90 degrees as the centered default value for both servos.
  Servo1.write(90);
  Servo2.write(90);
  
  Serial.begin(9600);
}
// To read the distance of the  object from the sensor.
int readDistance(int pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW); // To reset the sensor to low state.
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pin, LOW);

  pinMode(pin, INPUT);

  int duration = pulseIn(pin, HIGH, timeout);

  if (duration == 0) // In case of a timeout
    return -1; 

  return duration / 74 / 2; // Distance in inches
}

void loop()
{
  int dl, dr, du, dd;
  du = readDistance(4);
  delay(20); // To prevent inteference between two sensors.
  dd = readDistance(5);
  if (du >= 0 && dd >= 0) // For valid distances only.
  {
    if (abs(du - dd) > range) // The difference the distance is within a certain small range.
    {
      if (du < dd && degree_ud < 90)
        degree_ud++; // Towards up direction.
      else if (du > dd && degree_ud > -90)
        degree_ud--; /// Towards down direction.
    }
	// Updating the servo motor angle.
    Servo1.write(90 + degree_ud);
  }
  
  dl = readDistance(6);
  delay(20); // To prevent inteference between two sensors.
  dr = readDistance(7);

  if (dl >= 0 && dr >= 0)
  {
    if (abs(dr - dl) > range)
    {
      if (dr < dl && degree_lr < 90)
        degree_lr++; // Towards left direction.
      else if (dr > dl && degree_lr > -90)
        degree_lr--; // Towards right direction.
    }
	// Updating the servo motor angle.
    Servo2.write(90 + degree_lr);
  }
  // For tracking current positions
  Serial.print("Up: ");
  Serial.print(du);
  Serial.print(" Down: ");
  Serial.print(dd);
  Serial.print(" Left: ");
  Serial.print(dl);
  Serial.print(" Right: ");
  Serial.print(dr);
  Serial.print(" Angle 1: ");
  Serial.print(degree_ud);
  Serial.print(" Angle 2: ");
  Serial.println(degree_lr);
  delay (100); // Providing time for servo motors to rotate.
}