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
    const float result = pow(10, (static_cast<float>(number) / this->series[series].values));
    // TODO: queee? It's off sometimes and I don't know why
    const uint8_t rounding = pow(10, this->series[series].precision - 1);
    return std::round(result * rounding) / rounding;
}

void StopResisting::newResistor() {
    this->multiplier =
            rand() %
            (this->series[this->current].max + 1 - this->series[this->current].min) +
            this->series[this->current].min;

    const uint8_t numInSet = rand() % this->series[this->current].values + 1;
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
        colors[2] = round(value / 0.01);
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
        strlen = snprintf(buffer, length, "%.2f %c\u2126\0", result, units[f]);
    }

    return strlen;
}


