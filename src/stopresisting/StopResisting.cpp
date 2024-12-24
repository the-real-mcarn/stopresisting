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

void StopResisting::newResistor() {
    this->multiplier = rand() % (6 + 1 - 2) + 2; // Smallest value for E96 is 100
    this->value = this->values[rand() % 97];
}

std::array<int, 4> StopResisting::getColors() const {
    std::array<int, 4> colors = { 0 };

    colors[0] = floor(this->value / 1.0);
    colors[1] = floor((this->value - (colors[0]*1.0)) / 0.1);
    colors[2] = floor((this->value - (colors[0]*1.0) - (colors[1]*0.1)) / 0.01);
    colors[3] = this->multiplier - 2; // Color is 2 sets off because of comment above
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
        char units[3] = { ' ', 'k', 'M'};
        float value = this->getValue();
        char f = floor(log(value)/log(1000)); // Find if ohms (0), kiloohms (1) or megaohms (2)
        float result = value/static_cast<float>(pow(1000, f)); // Recalculate value keeping in mind unit
        snprintf(buffer, sizeof(buffer), "%.2f %c\u2126\0", result, units[f]);
    }

    return buffer;
}


