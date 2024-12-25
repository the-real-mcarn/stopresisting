#include <iostream>
#include <cmath>

#include "stopresisting/StopResisting.h"
#include <ctime>
#include <valarray>

StopResisting res(time(nullptr));

unsigned char ansii[] = {234, 52, 196, 202, 11, 10, 20, 201, 243, 255};

int main() {
    std::cout << "=== Resistor Guesser ===" << std::endl << "== MS Windows Edition ==" << std::endl;

    // Set current set
    res.setSeries(Series::E96);

    // Print all resistors in set to check values
    for (int i = 0; i < res.series[res.current].values; ++i) {
        std::printf("%d:\t%.2f\n", i, res.getResistorNr(res.current, i));;
    }

    // Random series test
    res.newResistor();

    std::printf("Value:\t\t%.2f\n", res.value);
    std::printf("Multiplier:\t%d\n", res.multiplier);
    std::printf("\t\t\t%0.f\n", pow(10, res.multiplier));
    std::printf("Ohm value:\t%.2f \u2126\n", res.getValue());

    const std::string valstr = res.getValueStr();
    std::printf("Formatted:\t%s\n", valstr.c_str());

    const std::array<int8_t, 4> colors = res.getColors();

    std::cout << "Numbers:\t";
    for (int i = 0; i< 4; i++)
        std::printf("%d ", colors.at(i));
    std::cout << std::endl << std::endl;

    std::cout << "--[\033[48;5;123m ";
    for (int i = 0; i < 4; i++) {
        if (colors[i] == -1)
            continue;

        char output[48];
        sprintf(output, "\033[48;5;123m\033[38;5;%dm\u258A\033[0m", ansii[colors[i]]);
        std::cout << output;
    }
    std::cout << "\033[48;5;123m \033[0m]--" << std::endl;

    return 0;
}