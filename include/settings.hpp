#pragma once

#include <cstdint>

struct Config {
    uint8_t flags = 0b00000011;
    int keys[3]{82, 71, 80};
};

class Settings {
public:
    static void save();
    static void load();

    static bool getflag(uint8_t flag);
    static void setflag(uint8_t flag, bool value);
    
    static int getkey(int key);
    static void setkey(int key, int value);
    
    static bool checkerboard();
    static bool padding();
    
    static Config config;
};