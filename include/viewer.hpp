#pragma once

#include <filesystem>

#include <raylib.h>

class Viewer {
public:
    bool open(const std::filesystem::path& path);

    void update();
    void draw();

private:
    Texture2D texture{};

    void updateTransform();
    void drawBackground();

    float scale;
    Vector2 position;
};