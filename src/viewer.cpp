#include <viewer.hpp>

#include <vector2.hpp>

#include <cmath>
#include <algorithm>

constexpr int padding = 20;

bool Viewer::open(const std::filesystem::path& path) {
    texture = LoadTexture(path.string().c_str());

    if (!IsTextureValid(texture)) return false;

    switch (texture.format) {
    case PIXELFORMAT_UNCOMPRESSED_GRAYSCALE:
    case PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA:
    case PIXELFORMAT_UNCOMPRESSED_R5G5B5A1:
    case PIXELFORMAT_UNCOMPRESSED_R4G4B4A4:
    case PIXELFORMAT_UNCOMPRESSED_R8G8B8A8:
    case PIXELFORMAT_UNCOMPRESSED_R32:
    case PIXELFORMAT_UNCOMPRESSED_R32G32B32A32:
        hasalpha = true;
        break;

    default:
        hasalpha = false;
        break;
    }
    
    getscale();

    _draw();
    return true;
}

void Viewer::draw() {
    amended();
    _draw();
}

Vector2 Viewer::getpos() {
    return {
        (GetScreenWidth() - ssize.x) / 2.0f,
        (GetScreenHeight() - ssize.y) / 2.0f
    };
}

void Viewer::getscale() {
    scale = std::min(
        static_cast<float>(GetScreenWidth() - padding * 2) / texture.width,
        static_cast<float>(GetScreenHeight() - padding * 2) / texture.height
    );
    float s = scale * zoom;
    ssize = {
        std::round(texture.width * s),
        std::round(texture.height * s)
    };
}

void Viewer::amended() {
    if (IsWindowResized()) getscale();

    float wheel = GetMouseWheelMove();

    if (wheel == 0) return;

    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        Vector2 mouse = GetMousePosition();

        Vector2 relative = (mouse - getpos() - offset) / ssize;

        zoom = std::clamp(zoom * std::pow(1.1f, wheel), 0.5f, 200.0f);

        getscale();

        offset = mouse - getpos() - relative * ssize;
    } else {
        float val = wheel * 20;

        Vector2 center = {
            GetScreenWidth() / 2.0f,
            GetScreenHeight() / 2.0f
        };
    
        Vector2 pos = getpos();
    
        if (IsKeyDown(KEY_LEFT_SHIFT))
            offset.x = std::clamp(
                offset.x + val,
                center.x - pos.x - ssize.x,
                center.x - pos.x);
        else offset.y = std::clamp(offset.y + val,
            center.y - pos.y - ssize.y,
            center.y - pos.y);
    }
}

void Viewer::_draw() {
    ClearBackground({240, 240, 240, 255});

    grid();

    Rectangle src = {
        0.0f,
        0.0f,
        static_cast<float>(texture.width),
        static_cast<float>(texture.height)
    };

    Vector2 pos = getpos() + offset;
    Rectangle dst = {
        pos.x,
        pos.y,
        ssize.x,
        ssize.y
    };

    DrawTexturePro(texture, src, dst, {0, 0}, 0.0f, WHITE);
}

void Viewer::grid() {
    Vector2 pos = getpos() + offset;
    DrawRectangle(
        static_cast<int>(pos.x) - 1,
        static_cast<int>(pos.y) - 1,
        static_cast<int>(ssize.x) + 2,
        static_cast<int>(ssize.y) + 2,
        BLACK
    );

    if (!hasalpha) return;

    constexpr int size = 50;

    int left   = static_cast<int>(pos.x);
    int top    = static_cast<int>(pos.y);
    int right  = left + static_cast<int>(ssize.x);
    int bottom = top + static_cast<int>(ssize.y);

    int startY = top  + ((std::max(0, -top)  + size - 1) / size) * size;
    int endY = std::min(bottom, GetScreenHeight());

    int startX = left  + ((std::max(0, -left)  + size - 1) / size) * size;
    int endX = std::min(right, GetScreenWidth());

    DrawRectangle(startX, startY, endX - startX, endY - startY, {255, 255, 255, 255});

    for (int y = startY; y < endY; y += size) {
        for (int x = startX; x < endX; x += size) {
            if (((x / size) + (y / size)) % 2 == 0) DrawRectangle(
                x, y,
                std::min(size, right - x),
                std::min(size, bottom - y),
                {224, 224, 224, 255}
            );
        }
    }
}