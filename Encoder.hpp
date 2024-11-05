#pragma once

#include <Arduino.h>

class DualEncoder {
public:
		const uint8_t mot1_int, mot1_dir, mot2_int, mot2_dir;
		volatile int8_t direction;
		float position = 0;
		uint16_t counts_per_revolution = 695;
		volatile long countMot1 = 0;
		volatile long countMot2 = 0;
		uint32_t prev_time;
		bool read = false;

		// initialise both encoders
		DualEncoder(uint8_t enc1, uint8_t enc2,uint8_t enc3, uint8_t enc4) : mot1_int(enc1), mot1_dir(enc2), mot2_int(enc3), mot2_dir(enc4) {
				instance = this;  // Store the instance pointer
				pinMode(mot1_int, INPUT_PULLUP);
				pinMode(mot1_dir, INPUT_PULLUP);
				pinMode(mot2_int, INPUT_PULLUP);
				pinMode(mot2_dir, INPUT_PULLUP);
				
				attachInterrupt(digitalPinToInterrupt(mot1_int), DualEncoder::readEncoder1ISR, RISING);
				attachInterrupt(digitalPinToInterrupt(mot2_int), DualEncoder::readEncoder2ISR, RISING);
		}

		// Encoder function used to update the encoder
		void readEncoder1() {
				noInterrupts();
				direction = digitalRead(mot1_dir) ? 1 : -1;
				countMot1 += direction;
				interrupts();
		}
		void readEncoder2() {
				noInterrupts();
				direction = digitalRead(mot2_dir) ? 1 : -1;
				countMot2 += direction;
				interrupts();
		}

		// Helper function which to convert encouder count to radians
		float getRotation1() {
				return (static_cast<float>(countMot1) / counts_per_revolution ) * 2 * PI;
		}
		float getRotation2() {
				return (static_cast<float>(countMot2) / counts_per_revolution ) * 2 * PI;
		}

		void reset() {
				countMot1 = 0;
				countMot2 = 0;
		}

private:
		static DualEncoder* instance;

    static void readEncoder1ISR() {
        if (instance != nullptr) {
            instance->readEncoder1();
        }
    }

   static void readEncoder2ISR() {
        if (instance != nullptr) {
            instance->readEncoder2();
        }
    }
}

// Define the static instance pointer
DualEncoder* DualEncoder::instance = nullptr;