#include "src/thermistor.h"
Thermistor thermistor(A0);

void setup() {
  Serial.begin(115200);
}

void loop() {
  thermistor.print_resistance(5.0, 100000.0, 1024);
}
