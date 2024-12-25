//
// Created by User on 24-12-2024.
//

#ifndef STOPRESISTING_H
#define STOPRESISTING_H

#include <array>
#include <cstdint>
#include <string>

enum Colors {
    Pink = -3,
    Silver = -2,
    Gold = -1,
    Black,
    Brown,
    Red,
    Orange,
    Yellow,
    Green,
    Blue,
    Violet,
    Grey,
    White,
};

struct SeriesData {
    uint8_t values; // Amount of values in set
    uint8_t bands; // Number of bands on set excluding the tolerance, we don't care about that one
    uint8_t min; // Minimum multiplier of resistor, e.g. smallest resistor for E96 is 100 so the multiplier is 2 (10^2)
    uint8_t max; // Maximum multiplier, usually 6; But we'll put it here for completeness
};

enum Series {
    E12,E24,E96,
};

class StopResisting {
private:
    Series current = Series::E96;
    SeriesData series[3] {
        {12, 3, 1, 6},
        {24, 4, 2, 6},
        {96, 4, 2, 6}
    };

public:
    // Current guess set
    int multiplier = 0; // 10^multiplier
    float value = 0.0;

    explicit StopResisting(int seed);

    void setSeries(Series series);
    void newResistor();
    std::array<int, 4> getColors() const;
    float getValue();
    std::string getValueStr();
};

#endif //STOPRESISTING_H
