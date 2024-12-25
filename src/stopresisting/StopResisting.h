//
// Created by User on 24-12-2024.
//

#ifndef STOPRESISTING_H
#define STOPRESISTING_H

#include <array>
#include <cstdint>
#include <string>

enum Colors {
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
    Gold,
    Silver,
    Pink
};

struct SeriesData {
    uint8_t values; // Amount of values in set
    uint8_t bands; // Number of bands on set excluding the tolerance, we don't care about that one
    uint8_t min; // Minimum multiplier of resistor, e.g. smallest resistor for E96 is 100 so the multiplier is 2 (10^2)
    uint8_t max; // Maximum multiplier, usually 6; But we'll put it here for completeness
    uint8_t precision; // Number of significant digits, e.g. 3 for E96
};

enum Series {
    E12, E24, E96,
};

class StopResisting {
public:
    // Current guess set
    uint8_t multiplier = 0; // 10^multiplier
    float value = 0.0;
    Series current = Series::E96;

    // Dataset for resistor series
    SeriesData series[3]{
        {12, 3, 1, 6, 2},
        {24, 4, 2, 6, 2},
        {96, 4, 2, 6, 3}
    };

    /**
    * Initialise and seed rng
    * @param seed Some random value you have available on target to seed the random generator
    */
    explicit StopResisting(int seed);

    /**
    * Change current set, default is E96
    * @param series Series to use, e.g. Series::E96
    */
    void setSeries(Series series);

    /**
     * Function for checking correct generation of resistor series
     * Value is rounded to 0.01 accuracy
     * @param series Series to use
     * @param number Number of resistor in series
     * @return Value of that resistor
     */
    [[nodiscard]] float getResistorNr(Series series, uint8_t number) const;

    /**
    * Get a new random resistor
    */
    void newResistor();

    /**
    *
    * @return Array of numbers corresponding to the Colors enum
    */
    [[nodiscard]] std::array<int8_t, 4> getColors() const;

    /**
    * Get value
    * @return Value of current resistor in Ohms
    */
    [[nodiscard]] float getValue() const;

    /**
    * Formats the value of the current resistor to a string
    * E.g. 12000 Ohm --> 12KOhm
     * @return Value of current resistor as formatted string
    */
    [[nodiscard]] std::string getValueStr() const;
};

#endif //STOPRESISTING_H
