#include "Color.hpp"

namespace prog {
    Color::Color() {
        R=0;
        G=0;
        B=0;
    }
    Color::Color(const Color& other) {
        R=other.red();
        G=other.green();
        B=other.blue();
    }
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {
        R=red;
        G=green;
        B=blue;
    }
    rgb_value Color::red() const {
        
        return R;
    }
    rgb_value Color::green() const {
        return G;
    }
    rgb_value Color::blue() const {
        return B;
    }

    rgb_value& Color::red()  {
        return R;
    }
    rgb_value& Color::green()  {
        return G;
    }
    rgb_value& Color::blue()  {
        return B;
    }
     bool Color::operator==(const Color& Color2) const{ //compares two Colors - for equal
        if (R==Color2.R && G==Color2.G && B==Color2.B){
            return true;
        }
        return false;
    }
}