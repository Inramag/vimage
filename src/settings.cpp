#include <settings.hpp>

#include <fstream>

uint8_t Settings::flags = 0b00000011;

void Settings::save() {
    std::ofstream file("conf.bin", std::ios::binary);
    file.write(reinterpret_cast<const char*>(&flags), 1);
}

void Settings::load() {
    std::ifstream file("conf.bin", std::ios::binary);
    if (!file) {
        save();
        return;
    }
    file.read(reinterpret_cast<char*>(&flags), 1);
}

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