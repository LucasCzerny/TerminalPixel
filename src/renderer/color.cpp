#include "color.hpp"

#include <iostream>

namespace tp {
    void set_text_color(Color color) {
        std::cout << "\033[1;" << static_cast<unsigned int>(color) << "m";
    }

    void set_background_color(ClearColor color) {
        std::cout << "\033[1;" << static_cast<unsigned int>(color) << "m";
    }
}
