#include "thermistor.h"

#include "Arduino.h"

Thermistor::Thermistor(int _pin, int _adc_max_value, int _n_samples, int _sampling_interval_ms) {
  Thermistor::pin = _pin;
  Thermistor::adc_max_value = _adc_max_value;
  Thermistor::n_samples = _n_samples;
  Thermistor::sampling_interval_ms = _sampling_interval_ms;
}

double Thermistor::__compute_resistance(int adc_reading, int thermistor_base_resistance) {
  // Some magical trickery I have no idea why it works but it works so damn well.
  int base_resistance = thermistor_base_resistance / 10;

  return ((adc_max_value * base_resistance) / (double) adc_reading) - base_resistance;
}

int Thermistor::average_adc_reading() {
  int *raw_samples = new int[n_samples];
  int sum_samples = 0;

  for (int i = 0; i < n_samples; i++) {
    raw_samples[i] = analogRead(pin);
    sum_samples += raw_samples[i];
    delay(sampling_interval_ms);
  }

  return sum_samples / n_samples;
}

[[noreturn]] void Thermistor::print_resistance(float v_in, float r_1, int adc_max_value) {
  float buffer, v_out, r_2;
  int raw_adc;

  while (true) {
    raw_adc = average_adc_reading();

    if (raw_adc) {
      // Compute the resistance of the thermistor
      buffer = raw_adc * v_in;
      v_out = buffer / adc_max_value;
      buffer = (v_in / v_out) - 1;
      r_2 = r_1 * buffer;

      Serial.print("V_out: ");
      Serial.print(v_out);
      Serial.print(" - ");
      Serial.print("R_2: ");
      Serial.println(r_2);
      delay(1000);
    }
  }
}
