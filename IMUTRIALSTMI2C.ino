#include <Arduino_LSM9DS1.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x09 // I2C address of the Arduino Mega

// Time variables for acceleration  
unsigned long previousMillisAccel = 0;
const long intervalAccel = 10; // Interval for reading acceleration data in milliseconds

// Time variables for gyroscope
unsigned long prevTime;
unsigned long currTime;
unsigned long previousMillisGyro = 0;
const long intervalGyro = 10; // Interval for reading gyroscope data in milliseconds

// Velocity and displacement variables for acceleration
float velX = 0, velY = 0;
float dispX = 0, dispY = 0;

float accelX = 0.0, accelY = 0.0, accelZ = 0.0;

// Variables to store angle values from gyroscope
float angleX = 0.0, angleY = 0.0, angleZ = 0.0;

void setup() {
  Serial.begin(115200);
  Wire.begin(); // Join I2C bus as master
  
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  Serial.println("IMU initialized successfully.");
  
  prevTime = millis();
}

void loop() {
  // Current time for acceleration data
  unsigned long currentMillisAccel = millis();

  // Read acceleration data at regular intervals
  if (currentMillisAccel - previousMillisAccel >= intervalAccel) {
    previousMillisAccel = currentMillisAccel;

    // Read acceleration data
    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(accelX, accelY, accelZ);

      // Convert from g to m/s^2
      accelX *= 9.80665;
      accelY *= 9.80665;

      // Calculate time elapsed in seconds for acceleration
      float deltaTimeAccel = intervalAccel / 1000.0;

      // Only update if movement threshold is exceeded
      if(accelX > 1.4 || accelX < -1.4 || accelY > 0.652 || accelY < -0.652) {
        velX += accelX * deltaTimeAccel;
        velY += accelY * deltaTimeAccel;

        // Update displacements by integrating velocity
        dispX += (velX * deltaTimeAccel);
        dispY += (velY * deltaTimeAccel);
      }
    }
  }

  // Current time for gyroscope data
  unsigned long currentMillisGyro = millis();

  // Read gyroscope data at regular intervals
  if (currentMillisGyro - previousMillisGyro >= intervalGyro) {
    previousMillisGyro = currentMillisGyro;

    // Read gyroscope data
    if (IMU.gyroscopeAvailable()) {
      float gyroX, gyroY, gyroZ;
      IMU.readGyroscope(gyroX, gyroY, gyroZ);
      currTime = millis();

      // Calculate time elapsed in seconds for gyroscope
      float deltaTimeGyro = (currTime - prevTime) / 1000.0;
      prevTime = currTime;

      if(gyroX > 0.9 || gyroX < -0.9 || gyroY > 1 || gyroY < -1 || gyroZ > 1 || gyroZ < -1) {
        // Integrate gyroscope data to get angles (in degrees)
        angleX += gyroX * deltaTimeGyro * 1.2011236;
        angleY += gyroY * deltaTimeGyro * 1.1411236;
        angleZ += (gyroZ * deltaTimeGyro) * 1.1416;

        // Keep angles within -180 to 180 degrees
        angleX = fmod(angleX, 360.0);
        if (angleX >= 180.0) angleX -= 360.0;
        if (angleX <= -180.0) angleX += 360.0;

        angleY = fmod(angleY, 360.0);
        if (angleY >= 180.0) angleY -= 360.0;
        if (angleY <= -180.0) angleY += 360.0;

        angleZ = fmod(angleZ, 360.0);
        if (angleZ >= 180.0) angleZ -= 360.0;
        if (angleZ <= -180.0) angleZ += 360.0;
        // Send angleZ to Arduino Mega via I2C
        Wire.beginTransmission(SLAVE_ADDRESS);
        Wire.write((byte*)&angleZ, sizeof(angleZ)); // Send angleZ as bytes
        Wire.endTransmission();

        // Print angles
        Serial.print("Angle - X: ");
        Serial.print(angleX);
        Serial.print(" ");
        Serial.print(" Angel, Y: ");
        Serial.print(angleY);
        Serial.print(" ");
        Serial.print(" deg, Z: ");
        Serial.print(angleZ);
        Serial.println("");
      }
    }
  }
          Wire.beginTransmission(SLAVE_ADDRESS);
        Wire.write((byte*)&angleZ, sizeof(angleZ)); // Send angleZ as bytes
        Wire.endTransmission();
}
