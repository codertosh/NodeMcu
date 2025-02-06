#include "ACS712.h"

#define ACS712_PIN 34  // Analog pin where ACS712 is connected
#define VREF 3.3       // ESP32 ADC reference voltage
#define ADC_RES 4095   // ESP32 ADC resolution (12-bit)
#define SENSITIVITY 66 // ACS712 30A model sensitivity (mV/A)

ACS712 ACS(ACS712_PIN, VREF, ADC_RES, SENSITIVITY);

float zeroCurrent = .167; // Offset correction (Adjust this based on no-load readings)

void setup() {
  Serial.begin(115200);
  Serial.println("ACS712 Current Sensor Test");
  delay(2000);  // Allow time for the sensor to stabilize
}

void loop() {
  float current = readCurrent();
  
  Serial.print("Measured Current: ");
  Serial.print(current, 3); // Show 3 decimal places
  Serial.println(" A");

  delay(1000); // Wait 1 second before the next reading
}

float readCurrent() {
  float average = 0;
  int samples = 100; // Number of readings for averaging

  for (int i = 0; i < samples; i++) {
    average += ACS.mA_AC();  // Read AC current in milliamps
    delay(2);  // Small delay between samples to reduce noise
  }

  float current_A = abs(average / samples) / 1000.0; // Convert mA to A

  // Offset correction
  current_A -= zeroCurrent;   // Subtract the idle value

  if (current_A < 0.005) current_A = 0; // Ignore small fluctuations

  return current_A;
}
