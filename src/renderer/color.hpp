#pragma once

namespace tp {

    enum class Color {
        reset = 39,
        black = 30,
        red = 31,
        green = 32,
        yellow = 33,
        blue = 34,
        magenta = 35,
        cyan = 36,
        white = 37
    };

    enum class ClearColor {
        reset = 49,
        black = 40,
        red = 41,
        green = 42,
        yellow = 44,
        blue = 44,
        magenta = 45,
        cyan = 46,
        white = 47
    };

    void set_text_color(Color color);
    void set_background_color(ClearColor color);
}
