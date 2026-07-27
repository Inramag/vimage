#pragma once

#include <cstdint>

class Settings {
public:
    static bool get(uint8_t flag);
    static void set(uint8_t flag, bool value);
    
    static bool checkerboard();
    static bool padding();

private:
    static uint8_t flags;
};