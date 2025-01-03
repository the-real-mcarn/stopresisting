//
// Created by User on 24-12-2024.
//

#include "StopResisting.hpp"
#include <cmath>
#include <cstdlib>
#include <cstdio>

StopResisting::StopResisting(int seed) {
    std::srand(seed);
}

void StopResisting::setSeries(Series series) {
    this->current = series;
}

float StopResisting::getResistorNr(const Series series, const uint8_t number) const {
    float result = pow(10, (static_cast<float>(number) / this->series[series].values));
    result += this->getParisCorrection(this->series[series].values, number);
    const uint8_t rounding = pow(10, this->series[series].precision - 1); // Number of decibals to power of 10
    return std::round(result * rounding) / rounding;
}

float StopResisting::getParisCorrection(const uint8_t series, const uint8_t number) {
    float result = 0;
    
    // may the resistor God help you if you use E3;
    if(series == 24 ||  series == 12 || series == 6  || series == 3 ) { 
        // if n is not an element of E24, correct it to be part of the set
        switch(const int n24 = number * (24 / series)) {
            case 10 ... 16:
                result = 0.1;
                break;
            case 22:
                result = -0.1;
                break;
            default:
                break;
        }
    }

    return result;
}

void StopResisting::newResistor() {
    this->multiplier =
            rand() %
            (this->series[this->current].max + 1 - this->series[this->current].min) +
            this->series[this->current].min;

    const uint8_t numInSet = rand() % this->series[this->current].values; // Resistors 0-95 for E96 series
    this->value = this->getResistorNr(this->current, numInSet);
}

uint8_t StopResisting::getColors(int8_t *colors, uint8_t length) const {
    float value = this->value;

    colors[0] = floor(value / 1.0);
    value = value - colors[0] * 1.0;

    colors[1] = floor(value / 0.1);
    value = value - colors[1] * 0.1;

    // TODO: This sometimes just dies, maybe fix that
    if (this->series[this->current].bands == 3) {
        colors[2] = this->multiplier - 2; // Color is 2 sets off because of comment above
        colors[3] = -1;
        return 3;
    } else {
        // Sometimes the float will become e.g. 0.01999 instead of 0.02, which will cause the method above to be 1 off
        colors[2] = floor(value / 0.01);
        colors[3] = this->multiplier - 2; // Color is 2 sets off because of comment above
        return 4;
    }
}

float StopResisting::getValue() const {
    return this->value * pow(10, this->multiplier);
}

int StopResisting::getValueStr(char *buffer, uint8_t length) const {
    int strlen = 0;

    if (value == 0) {
        strlen = snprintf(buffer, length, "0 \u2126");
    } else {
        constexpr char units[4] = {' ', 'k', 'M', 'G'};
        const float value = this->getValue();
        const char f = floor(log(value) / log(1000)); // Find if ohms (0), kiloohms (1), megaohms (2), etc.
        const float result = value / static_cast<float>(pow(1000, f)); // Recalculate value keeping in mind unit
        strlen = snprintf(buffer, length, "%.2f %cOhm\0", result, units[f]);
    }

    return strlen;
}

uint8_t StopResisting::guess(int8_t *guess, uint8_t length) const {
    uint8_t result = 0;

    int8_t colors[4] = {0};
    const uint8_t len = this->getColors(colors);

    for (uint8_t i = 0; i < len; i++) {
        char shift = (colors[i] == guess[i]) ? 1 : 0;
        result = (result << 1) | shift;
    }

    return result;
}



