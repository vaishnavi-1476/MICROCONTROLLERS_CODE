#include <Arduino_LSM9DS1.h>

// Variables to store angle values
float angleX = 0.0, angleY = 0.0, angleZ = 0.0;

// Time variables
unsigned long prevTime;
unsigned long currTime;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Gyroscope in degrees/second");
  Serial.println("X\tY\tZ");

  // Initialize time
  prevTime = millis();
}

void loop() {
  float x, y, z;

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);

    // Get current time
    currTime = millis();
    // Calculate time difference in seconds
    float deltaTime = (currTime - prevTime) / 1000.0;
    // Update previous time
    prevTime = currTime;
if(x>0.5 || x<-0.5 || y>2.1 || y<-2.1 || z>1 || z<-1)
{
    // Integrate angular velocity to get angles
    angleX += x * deltaTime;
    angleY += y * deltaTime;
    angleZ += z * deltaTime;

    // Print angular velocities and angles
    Serial.print("Angular velocity (deg/s): ");
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.print(z);
    Serial.println();

    Serial.print("Angle (deg): ");
    Serial.print(angleX);
    Serial.print('\t');
    Serial.print(angleY);
    Serial.print('\t');
    Serial.println(angleZ);
}
  }
}
