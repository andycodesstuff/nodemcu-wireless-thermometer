#ifndef Thermistor_h
#define Thermistor_h

/**
 * A thermistor is a resistor whose resistance is dependant on temperature. There are 2 types of thermistors:
 *  - NTC (Negative Temperature Coefficient) thermistors, which decrease their resistance as the temperature raises
 *  - PTC (Positive Temperature Coefficient) thermistors, which increase their resistance as the temperature raises
 * 
 * Most electronic thermometers, are the former type.
 */
class Thermistor {
  private:
    const static int DEFAULT_N_SAMPLES = 10;
    const static int DEFAULT_SAMPLING_INTERVAL_MS = 50;

    int pin;
    int n_samples;
    int sampling_interval_ms;

  public:
    /**
     * Constructor.
     */
    Thermistor(int _pin,
               int _n_samples = Thermistor::DEFAULT_N_SAMPLES,
               int _sampling_interval_ms = Thermistor::DEFAULT_SAMPLING_INTERVAL_MS);

    /**
     * Samples multiple analog values from a pin and returns an average of the results.
     */
    int average_adc_reading();

    /**
     * Prints the resistance value of the thermistor. Follow this guide to build the test circuit:
     * https://www.circuitbasics.com/arduino-ohm-meter/ 
     * 
     * (NOTE: this method is used only for debugging purposes and uses an infinite loop and thus it will NOT return)
     * 
     * @param v_in The voltage of the test circuit (usually either 3.3V or 5V)
     * @param r_1 The resistance value (in ohms) of the known resistor in the test circuit. Note that to provide meaningful
     *            readings, the value of the known resistor should be closer to the value of the thermistor. For example,
     *            to find the resistance of a 220K ohm thermistor, a 100K ohm known resistor should yield decent results while
     *            a 1K ohm resistor will yield results with a margin of error greater than 100%. Choosing the known resistor
     *            is therefore crucial for accurate readings
     * @param max_adv_value The maximum value supported by the ADC unit. For example, for an Arduino Due this value is
     *                      1024 since the resolution of its ADC is 8 bits (therefore, 2 ^ 8 = 1024)
     */
    [[noreturn]] void print_resistance(float v_in, float r_1, int max_adc_value);
};

#endif
