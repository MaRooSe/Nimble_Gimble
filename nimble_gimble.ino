#include "Encoder.hpp"
//#include "IMU.hpp" // maybe not needed
//#include "Motor.hpp" // maybe not needed

// includes for IMU
#include <Wire.h> // need to download this libary from arduino IDE
#include <SparkFun_MMA8452Q.h> // need to download this libary from arduino IDE

// initialize IMU under the name "imu"
MMA8452Q imu;

// define motor pins
#define MOTOR1_PWM 11   // Example PWM pin for Motor 1 speed control
#define MOTOR1_DIR 12   // Example direction pin for Motor 1
#define MOTOR2_PWM 9    // Example PWM pin for Motor 2 speed control
#define MOTOR2_DIR 10   // Example direction pin for Motor 2
// define motor encoder pins
#define EN_1_A 2        // These are the pins for the PCB encoder
#define EN_1_B 7        // These are the pins for the PCB encoder
#define EN_2_A 3        // These are the pins for the PCB encoder
#define EN_2_B 8        // These are the pins for the PCB encoder
DualEncoder encoder(EN_1_A, EN_1_B, EN_2_A, EN_2_B);

// define max motor speed (max PWM is 255)
#define MAX_SPEED 255

/////////////////////
// Motor functions //
/////////////////////

// initialise motor
void initMotors() {
    pinMode(MOTOR1_PWM, OUTPUT);
    pinMode(MOTOR1_DIR, OUTPUT);
    pinMode(MOTOR2_PWM, OUTPUT);
    pinMode(MOTOR2_DIR, OUTPUT);
}

// ignore this (for another function)
void setMotor(int motor, int speed, int direction) {
    if (motor == 1) {
        digitalWrite(MOTOR1_DIR, !direction);
        analogWrite(MOTOR1_PWM, speed);
    } else if (motor == 2) {
        digitalWrite(MOTOR2_DIR, !direction);
        analogWrite(MOTOR2_PWM, speed);
    }
}

// set motor speed (- is bacwards | + is forwards)
void setMotorSpeed(int motor, float speed) {
    int direction = speed < 0 ? 0 : 1;
    speed = abs(speed);
    int val = MAX_SPEED * speed;

    if (motor == 1) {
        setMotor(1, val, direction);
    } else if (motor == 2) {
        setMotor(2, val, !direction);
    }
}

// really? you need a comment to know what this does?
void stopMotors() {
    setMotorSpeed(1, 0);
    setMotorSpeed(2, 0);
    Serial.println("Motors stopped!");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // start imu
  imu.init();

  // start motor
  initMotors();
  setMotorSpeed(1, 0.01);
  delay(50); // 0.5s break
  stopMotors();


}

void loop() {
  // put your main code here, to run repeatedly:

}
