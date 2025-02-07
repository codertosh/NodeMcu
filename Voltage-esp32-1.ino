
// https://diyprojectslab.com/interfacing-zmpt101b-voltage-sensor-with-esp32/

#include <Wire.h>
#include <ZMPT101B.h>

#define SENSITIVITY 500.0f       // Adjust this value to calibrate sensitivity
#define CALIBRATION_FACTOR 1.293  // Calibration factor to correct the reading (230 / 155)

ZMPT101B voltageSensor(34, 50.0);

void setup() {
  Serial.begin(115200);
  voltageSensor.setSensitivity(SENSITIVITY);
}

void sensor() {
  float voltage = voltageSensor.getRmsVoltage() * CALIBRATION_FACTOR;  // Apply calibration factor
  Serial.print("Voltage: ");
  Serial.println(voltage);
}

void loop() {
  sensor();
  delay(200);
}
