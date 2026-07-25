#pragma once

#include <filesystem>

#include <raylib.h>

class Viewer {
public:
    bool open(const std::filesystem::path& path);

    void draw();

private:
    Texture2D texture;

    Vector2 getpos();
    void getscale();

    void amended();

    void _draw();
    void grid();

    float scale;
    float zoom = 1;
    Vector2 ssize;
    Vector2 offset;
    Vector2 userPosition;
};