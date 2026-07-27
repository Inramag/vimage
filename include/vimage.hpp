#pragma once

#include <filesystem>

#include <vector>

enum class VFormat {
    unknown,
    png, jpg
};

struct VFrame {
    std::vector<unsigned char> pixels;
};

struct VImage {
    int width = 0;
    int height = 0;
    bool hasalpha = false;
    VFormat format = VFormat::unknown;

    std::vector<VFrame> frames{};

    static VImage load(const std::filesystem::path& path);
};