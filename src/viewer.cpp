#include <viewer.hpp>

#include <cmath>

constexpr int padding = 20;

bool Viewer::open(const std::filesystem::path& path) {
    texture = LoadTexture(path.string().c_str());
    bool isvalid = IsTextureValid(texture); 
    if (isvalid) updateTransform();
    return isvalid;
}

void Viewer::update() {
    if (IsWindowResized()) updateTransform();
}

void Viewer::draw() {
    drawBackground();

    Rectangle src = {
        0.0f,
        0.0f,
        static_cast<float>(texture.width),
        static_cast<float>(texture.height)
    };

    Rectangle dst = {
        position.x,
        position.y,
        ssize.x,
        ssize.y
    };

    DrawTexturePro(texture, src, dst, {0, 0}, 0.0f, WHITE);
}

void Viewer::updateTransform() {
    scale = std::min(
        static_cast<float>(GetScreenWidth() - padding * 2) / texture.width,
        static_cast<float>(GetScreenHeight() - padding * 2) / texture.height
    );

    ssize = {
        std::round(texture.width * scale),
        std::round(texture.height * scale)
    };

    position = {
        (GetScreenWidth() - ssize.x) / 2.0f,
        (GetScreenHeight() - ssize.y) / 2.0f
    };
}

void Viewer::drawBackground() {
    ClearBackground({ 230, 230, 230, 255 });

    DrawRectangle(
        static_cast<int>(position.x) - 1,
        static_cast<int>(position.y) - 1,
        static_cast<int>(ssize.x) + 2,
        static_cast<int>(ssize.y) + 2,
        BLACK
    );

    constexpr int size = 50;

    Color light = {255, 255, 255, 255};
    Color dark  = {224, 224, 224, 255};

    int left   = static_cast<int>(position.x);
    int top    = static_cast<int>(position.y);
    int right  = left + static_cast<int>(ssize.x);
    int bottom = top + static_cast<int>(ssize.y);

    for (int y = top; y < bottom; y += size) {
        for (int x = left; x < right; x += size) {
            bool even = ((x / size) + (y / size)) % 2 == 0;

            DrawRectangle(
                x,
                y,
                std::min(size, right - x),
                std::min(size, bottom - y),
                even ? light : dark
            );
        }
    }
}