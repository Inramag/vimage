#pragma once

#include <filesystem>

#include <vector>

#include <raylib.h>

enum class Format {
    unknown,
    png, jpg
};

struct Frame {
    std::vector<unsigned char> pixels;
};

struct VImage {
    int width = 0;
    int height = 0;
    bool hasalpha = false;
    Format format = Format::unknown;

    std::vector<Frame> frames{};

    void get(Texture& texture);

    static VImage load(const std::filesystem::path& path);
};