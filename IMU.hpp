#ifndef MMA8452QEXAMPLE_HPP
#define MMA8452QEXAMPLE_HPP

#include <Wire.h> // Must include Wire library for I2C
#include <SparkFun_MMA8452Q.h> // Includes the SFE_MMA8452Q library
// Begin using the library by creating an instance of the MMA8452Q
//  class. We'll call it "accel". That's what we'll reference from
//  here on out.

class IMU {
public:
    // Constructor
    IMU() : accel() {}

    // Initialize the accelerometer
    void IMUStart() {
        accel.init();
    }

    // read IMU data 
    void readIMU() {
      if (accel.available()) {
        accel.read();
        // print out the calculated data
        printCalculatedAccels();
      }
    }

private:
    MMA8452Q accel;

    // print the calculated IMU data
    void printCalculatedAccels()
    { 
      Serial.print(accel.cx, 3);
      Serial.print("\t");
      Serial.print(accel.cy, 3);
      Serial.print("\t");
      Serial.print(accel.cz, 3);
      Serial.print("\t");
    }
}
#endif // MMA8452QEXAMPLE_HPP