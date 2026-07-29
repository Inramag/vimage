#include <settings.hpp>

#include <fstream>

Config Settings::config{};

void Settings::save() {
    std::ofstream file("conf.bin", std::ios::binary);
    file.write(reinterpret_cast<const char*>(&config), sizeof(config));
}

void Settings::load() {
    std::ifstream file("conf.bin", std::ios::binary);
    if (!file) {
        save();
        return;
    }
    file.read(reinterpret_cast<char*>(&config), sizeof(config));
}

bool Settings::getflag(uint8_t flag) {
    return config.flags & flag;
}
void Settings::setflag(uint8_t flag, bool value) {
    if (value) config.flags |= flag;
    else config.flags &= ~flag;
    save();
}

int Settings::getkey(int key) {
    return config.keys[key];
}
void Settings::setkey(int key, int value) {
    config.keys[key] = value;
    save();
}

bool Settings::checkerboard() {
    return getflag(0b00000001);
}

bool Settings::padding() {
    return getflag(0b00000010);
}