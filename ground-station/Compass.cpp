#include "Compass.h"
#include "Configuration.h"

Compass::Compass() {
  
  if (!sensor.begin()) {
    DEBUG_PRINTLN("Could not find a valid HMC5883L sensor, check wiring!");
    return;
  }
  
  sensor.setRange(HMC5883L_RANGE_1_3GA);
  sensor.setMeasurementMode(HMC5883L_CONTINOUS);
  sensor.setDataRate(HMC5883L_DATARATE_30HZ);
  sensor.setSamples(HMC5883L_SAMPLES_8);
  //sensor.setOffset(0, 0);
  sensor.setOffset(41, -106);
}

int previousDegree;

/*void Compass::tick() {
  long x = micros();
  Vector norm = sensor.readNormalize();

  // Calculate heading
  float heading = atan2(norm.YAxis, norm.XAxis);

  // Set declination angle on your location and fix heading
  // You can find your declination on: http://magnetic-declination.com/
  // (+) Positive or (-) for negative
  // For Bytom / Poland declination angle is 4'26E (positive)
  // Formula: (deg + (min / 60.0)) / (180 / M_PI);
  float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;

  // Correct for heading < 0deg and heading > 360deg
  if (heading < 0)
  {
    heading += 2 * PI;
  }
 
  if (heading > 2 * PI)
  {
    heading -= 2 * PI;
  }

  // Convert to degrees
  float headingDegrees = heading * 180/M_PI; 

  // Fix HMC5883L issue with angles
  float fixedHeadingDegrees;
 
  if (headingDegrees >= 1 && headingDegrees < 240)
  {
    fixedHeadingDegrees = map(headingDegrees, 0, 239, 0, 179);
  } else
  if (headingDegrees >= 240)
  {
    fixedHeadingDegrees = map(headingDegrees, 240, 360, 180, 360);
  }

  // Smooth angles rotation for +/- 3deg
  int smoothHeadingDegrees = round(fixedHeadingDegrees);

  if (smoothHeadingDegrees < (previousDegree + 3) && smoothHeadingDegrees > (previousDegree - 3))
  {
    smoothHeadingDegrees = previousDegree;
  }
  
  previousDegree = smoothHeadingDegrees;

  // Output
  Serial.print(headingDegrees);
  Serial.print(" : ");
  Serial.print(fixedHeadingDegrees);
  Serial.print(" : ");
  Serial.print(smoothHeadingDegrees);  
  Serial.println();
}*/

void Compass::tick() {
  Vector norm = sensor.readNormalize();

  // Calculate heading
  float heading = atan2(norm.YAxis, norm.XAxis);

  // Set declination angle on your location and fix heading
  // You can find your declination on: http://magnetic-declination.com/
  // (+) Positive or (-) for negative
  // For Bytom / Poland declination angle is 4'26E (positive)
  // Formula: (deg + (min / 60.0)) / (180 / M_PI);
  float declinationAngle = (8.0 + (37.0 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;

  // Correct for heading < 0deg and heading > 360deg
  if (heading < 0)
  {
    heading += 2 * PI;
  }

  if (heading > 2 * PI)
  {
    heading -= 2 * PI;
  }

  // Convert to degrees
  float headingDegrees = heading * 180/M_PI; 

  // Output
  Serial.print(" Heading = ");
  Serial.print(heading);
  Serial.print(" Degress = ");
  Serial.print(headingDegrees);
  Serial.println();
}

