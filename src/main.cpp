#include <cmath>
#include <iostream>
#include "stopresisting/StopResisting.hpp"
#include <ctime>
#include <conio.h>

#define DEBUG 1

StopResisting res(time(nullptr));
unsigned char ansii[] = {234, 52, 196, 202, 11, 10, 20, 201, 243, 255};

int main() {
    std::cout << "=== Resistor Guesser ===" << std::endl << "== MS Windows Edition ==" << std::endl;

    // Set current set and pick resistor
    res.setSeries(Series::E24);
    res.newResistor();

    // Get color bands
    int8_t colors[4] = {0};
    const uint8_t len = res.getColors(colors);

#if DEBUG
    // Print all resistors in set to check values
    for (int i = 0; i < res.series[res.current].values; ++i) {
        std::printf("%d:\t%.2f\n", i, res.getResistorNr(res.current, i));;
    }

    std::printf("Value:\t\t%.2f\n", res.value);
    std::printf("Multiplier:\t%d\n", res.multiplier);
    std::printf("\t\t\t%0.f\n", pow(10, res.multiplier));
    std::printf("Ohm value:\t%.2f \u2126\n", res.getValue());

    char buffer[16] = {0};
    res.getValueStr(buffer, sizeof(buffer));
    std::printf("Formatted:\t%s\n", buffer);

    std::cout << "Numbers:\t";
    for (int i = 0; i < len; i++)
        std::printf("%d ", colors[i]);
    std::cout << std::endl << std::endl;
#endif

    std::cout << "--[\033[48;5;123m ";
    for (int i = 0; i < 4; i++) {
        if (colors[i] == -1)
            continue;

        char output[48];
        sprintf(output, "\033[48;5;123m\033[38;5;%dm#\033[0m", ansii[colors[i]]);
        std::cout << output;
    }
    std::cout << "\033[48;5;123m \033[0m]--" << std::endl;

    // char input[4] = {0};
    // fgets(input, sizeof(input), stdin);

    // std::cout << input;

    char inputCh[4] = {0};

    fgets(inputCh, 5, stdin);
    printf("Input: %s\n", inputCh);

    int8_t input[4] = {0};
    for (int i = 0; i < 4; i++)
        input[i] = static_cast<int>(inputCh[i]) - 48; // ascii conversion magic

    uint8_t result = res.guess(input, 4);

#if DEBUG
    printf("Result: %d\n", result);
#endif

    for (int i = 0; i < len; i++)
        std::printf("%d", colors[i]);

    std::cout << std::endl;
    for (int i = 3; i >= 0; i--)
        std::cout << ((result >> i) & 1 ? ' ' : 'x');

    std::cout << std::endl;

    if (result == 15) {
        std::cout << "Correct" << std::endl;
    } else {
        std::cout << "Incorrect" << std::endl;
    }

    return 0;
}