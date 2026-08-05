#pragma once

#include <filesystem>
#include <cstdint>

struct Config {
    uint8_t flags = 0b00000011;
    int keys[3]{82, 71, 80};
};

namespace settings {
    void save();
    void load();

    bool getflag(uint8_t flag);
    void setflag(uint8_t flag, bool value);
    
    int getkey(int key);
    void setkey(int key, int value);
    
    bool checkerboard();
    bool padding();
    
    extern std::filesystem::path program;
    extern Config config;
};