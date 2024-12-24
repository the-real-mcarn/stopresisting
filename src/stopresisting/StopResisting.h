//
// Created by User on 24-12-2024.
//

#ifndef STOPRESISTING_H
#define STOPRESISTING_H

#include <array>
#include <string>

enum Colors {
    Black = 0,
    Brown = 1,
    Red   = 2,
    Orange = 3,
    Yellow = 4,
    Green  = 5,
    Blue   = 6,
    Violet  = 7,
    Grey   = 8,
    White  = 9,
};

enum Series {
    E12 = 0,
    E24 = 1,
    E96 = 2,
};

class StopResisting {
private:
    Series series = Series::E96;

    // Resistor values E96 series
    const float values[97] = {
        1.00, 1.02, 1.05, 1.07, 1.10, 1.13,
        1.15, 1.18, 1.21, 1.24, 1.27, 1.30,
        1.33, 1.37, 1.40, 1.43, 1.47, 1.50,
        1.54, 1.58, 1.62, 1.65, 1.69, 1.74,
        1.78, 1.82, 1.87, 1.91, 1.96, 2.00,
        2.05, 2.10, 2.16, 2.21, 2.26, 2.32,
        2.37, 2.43, 2.49, 2.55, 2.61, 2.67,
        2.74, 2.80, 2.87, 2.94, 3.01, 3.09,
        3.16, 3.24, 3.32, 3.40, 3.48, 3.57,
        3.65, 3.74, 3.83, 3.92, 4.02, 4.12,
        4.22, 4.32, 4.42, 4.53, 4.64, 4.75,
        4.87, 4.99, 5.11, 5.23, 5.36, 5.49,
        5.62, 5.76, 5.90, 6.04, 6.19, 6.34,
        6.49, 6.65, 6,81, 6.98, 7.15, 7.32,
        7.50, 7.68, 7.87, 8.06, 8.25, 8.45,
        8.66, 8.87, 9.09, 9.31, 9.53, 9.76
    };

public:
    // Current guess set
    int multiplier = 0; // 10^multiplier
    float value = 0.0;

    explicit StopResisting(int seed);

    void newResistor();
    std::array<int, 4> getColors() const;
    float getValue();
    std::string getValueStr();
};

#endif //STOPRESISTING_H
