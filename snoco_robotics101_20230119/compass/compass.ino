/*
===============================================================================================================
Based on QMC5883LCompass.h Library XYZ Example Sketch
https://github.com/mprograms/QMC5883LCompass
===============================================================================================================
*/
#include <QMC5883LCompass.h>

QMC5883LCompass compass;

void setup() {
  Serial.begin(115200);
  compass.init();
  
}

void loop() {
  int x, y, z;
  
  // Read compass values
  compass.read();

  // Return XYZ readings
  x = compass.getX();
  y = compass.getY();
  z = compass.getZ();

  float angle = atan2(x, y);
  angle += 3.14159;
  angle *= 57.296;
  
  Serial.print("angle: ");
  Serial.print(angle);
//  Serial.print(" X: ");
//  Serial.print(x);
//  Serial.print(" Y: ");
//  Serial.print(y);
//  Serial.print(" Z: ");
//  Serial.print(z);
  Serial.println();
  
  delay(250);
}
