#pragma once

#include <vimage.hpp>

#include <filesystem>

#include <raylib.h>

class Viewer {
public:
    bool open(const std::filesystem::path& path);

    void draw();
    
    void getscale();

private:
    VImage img;
    
    Texture2D texture;
    bool hasalpha;

    Vector2 getpos();

    void amended();

    void _draw();
    void grid();

    float scale;
    float zoom = 1;
    Vector2 ssize;
    Vector2 offset;
};