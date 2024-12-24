#include <iostream>
#include <math.h>

#include "stopresisting/StopResisting.h"
#include <time.h>
#include <valarray>

StopResisting res(time(NULL));

// enum Colors {
//     Black = 0,
//     Brown = 1,
//     Red   = 2,
//     Orange = 3,
//     Yellow = 4,
//     Green  = 5,
//     Blue   = 6,
//     Violet  = 7,
//     Grey   = 8,
//     White  = 9,
// };

unsigned char ansii[] = {234, 52, 196, 202, 11, 10, 20, 201, 243, 255};

int main() {
    std::cout << "=== Resistor Guesser ===" << std::endl << "== MS Windows Edition ==" << std::endl;

    res.newResistor();

    std::printf("Value:\t\t%f\n", res.value);
    std::printf("Multiplier:\t%d\n", res.multiplier);
    std::printf("\t\t\t%0.f\n", pow(10, res.multiplier));
    std::printf("Ohm value:\t%2.f \u2126\n", res.getValue());

    std::string valstr = res.getValueStr();
    std::printf("Formatted:\t%s\n", valstr.c_str());

    std::array<int, 4> colors = res.getColors();

    std::cout << "Numbers:\t";
    for (int i = 0; i< 4; i++)
        std::cout << colors.at(i) << " ";
    std::cout << std::endl << std::endl;

    std::cout << "--[\033[48;5;123m ";
    for (int i = 0; i < 4; i++) {
        char output[48];
        sprintf(output, "\033[48;5;123m\033[38;5;%dm\u258A\033[0m", ansii[colors[i]]);
        std::cout << output;
    }
    std::cout << "\033[48;5;123m \033[0m]--" << std::endl;

    return 0;
}