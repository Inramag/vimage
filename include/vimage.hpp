#pragma once

#include <filesystem>

#include <vector>

#include <raylib.h>

enum class Format {
    unknown,
    png, jpg,
    gif
};

struct Frame {
    Frame(std::vector<unsigned char> data, int w, int h, int _delay = 0) : pixels(data), delay(_delay) {
        if (IsWindowReady()) texture = LoadTextureFromImage({data.data(), w, h, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8});
    }
    
    std::vector<unsigned char> pixels;
    Texture texture;
    int delay;
};

struct VImage {
    int width = 0;
    int height = 0;
    bool hasalpha = false;
    Format format = Format::unknown;

    std::vector<Frame> frames{};

    static VImage load(const std::filesystem::path& path);
};
