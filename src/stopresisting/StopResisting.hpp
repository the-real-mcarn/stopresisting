//
// Created by User on 24-12-2024.
//

#ifndef STOPRESISTING_H
#define STOPRESISTING_H

#include <cstdint>

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
     * IEC63, Paris correction for E24 and subsets. 
     * Note: The Paris correction is not an official thing, I just thought it sounded cool.
     * @param series Series to use
     * @param number Number of resistor in series
     */
    float getParisCorrection(uint8_t series, uint8_t number) const;

    /**
    * Get a new random resistor
    */
    void newResistor();

    /**
     * Get the color bands of the resistor, numbers correspond to the Color enum, -1 means no band for E12 resistors
     * @param colors Buffer to put the values in
     * @param length Length of buffer provided, default 4 and I don't know why you would make it anything else
     * @return Returns actual number of values put in buffer-
     */
    [[nodiscard]] uint8_t getColors(int8_t *colors, uint8_t length = 4) const;

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
    int getValueStr(char *buffer, uint8_t length = 16) const;
};

#endif //STOPRESISTING_H
