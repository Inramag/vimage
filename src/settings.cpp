#include <settings.hpp>

uint8_t Settings::flags = 0b00000011;

bool Settings::get(uint8_t flag) {
    return flags & flag;
}
void Settings::set(uint8_t flag, bool value) {
    if (value) flags |= flag;
    else flags &= ~flag;
}

bool Settings::checkerboard() {
    return get(0b00000001);
}

bool Settings::padding() {
    return get(0b00000010);
}