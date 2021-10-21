#include "src/thermistor.h"
Thermistor thermistor(A0, 1024);

void setup() {
  Serial.begin(115200);
}

void loop() {
  double temp_C = thermistor.get_temperature_C();

  Serial.print("T: ");
  Serial.println(temp_C);
  delay(1000);
}
