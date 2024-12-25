//
// Created by User on 24-12-2024.
//

#include "StopResisting.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <valarray>
#include <array>
#include <iostream>
#include <ostream>

StopResisting::StopResisting(int seed) {
    std::srand(seed);
}

void StopResisting::setSeries(Series series) {
    this->current = series;
}

void StopResisting::newResistor() {
    this->multiplier =
        rand() %
        (this->series[this->current].max + 1 - this->series[this->current].min) +
        this->series[this->current].min;

    uint8_t numInSet = rand() % this->series[this->current].values + 1;
    float result = pow(10, (static_cast<float>(numInSet) / this->series[this->current].values));
    this->value = round(result * 100) / 100;
}

std::array<int, 4> StopResisting::getColors() const {
    std::array<int, 4> colors = { 0 };
    float value = this->value;

    colors[0] = floor(value / 1.0);
    value = value - colors[0] * 1.0;

    colors[1] = floor(value / 0.1);
    value = value - colors[1] * 0.1;

    if (this->series[this->current].bands == 3) {
        colors[2] = this->multiplier - 2; // Color is 2 sets off because of comment above
    } else {
        // Sometimes the float will become e.g. 0.01999 instead of 0.02, which will cause the method above to be 1 off
        colors[2] = round(value / 0.01);
        colors[3] = this->multiplier - 2; // Color is 2 sets off because of comment above
    }
    return colors;
}

float StopResisting::getValue() {
    return this->value * pow(10, this->multiplier);
}

std::string StopResisting::getValueStr() {
    char buffer[16] = { 0 };

    if (value == 0) {
        snprintf(buffer, sizeof(buffer), "0 \u2126");
    } else {
        char units[4] = { ' ', 'k', 'M', 'G' };
        float value = this->getValue();
        char f = floor(log(value)/log(1000)); // Find if ohms (0), kiloohms (1), megaohms (2), etc.
        float result = value/static_cast<float>(pow(1000, f)); // Recalculate value keeping in mind unit
        snprintf(buffer, sizeof(buffer), "%.2f %c\u2126\0", result, units[f]);
    }

    return buffer;
}


