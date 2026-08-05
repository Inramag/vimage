#include <settings.hpp>

#include <fstream>

std::filesystem::path settings::program;
Config settings::config;

void settings::save() {
    std::ofstream file(program / "conf.bin", std::ios::binary);
    file.write(reinterpret_cast<const char*>(&config), sizeof(config));
}

void settings::load() {
    std::ifstream file(program / "conf.bin", std::ios::binary);
    if (!file) {
        save();
        return;
    }
    file.read(reinterpret_cast<char*>(&config), sizeof(config));
}

bool settings::getflag(uint8_t flag) {
    return config.flags & flag;
}
void settings::setflag(uint8_t flag, bool value) {
    if (value) config.flags |= flag;
    else config.flags &= ~flag;
    save();
}

int settings::getkey(int key) {
    return config.keys[key];
}
void settings::setkey(int key, int value) {
    config.keys[key] = value;
    save();
}

bool settings::checkerboard() {
    return getflag(0b00000001);
}

bool settings::padding() {
    return getflag(0b00000010);
}