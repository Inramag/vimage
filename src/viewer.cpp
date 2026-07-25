#include <viewer.hpp>

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

    DrawTextureEx(texture, position, 0, scale, WHITE);
}

void Viewer::updateTransform() {
    scale = std::min(
        static_cast<float>(GetScreenWidth() - padding * 2) / texture.width,
        static_cast<float>(GetScreenHeight() - padding * 2) / texture.height
    );

    position = {
        (GetScreenWidth() - texture.width * scale) / 2.0f,
        (GetScreenHeight() - texture.height * scale) / 2.0f
    };
}

void Viewer::drawBackground() {
    ClearBackground({ 230, 230, 230, 255 });

    DrawRectangle(padding - 1, padding - 1, GetScreenWidth() - padding*2 + 2, GetScreenHeight() - padding*2 + 2, BLACK);

    constexpr int size = 50;

    Color light = {255, 255, 255, 255};
    Color dark  = {224, 224, 224, 255};

    for (int y = padding; y < GetScreenHeight() - padding; y += size) {
        for (int x = padding; x < GetScreenWidth() - padding; x += size) {
            bool even = ((x / size) + (y / size)) % 2 == 0;

            DrawRectangle(
                x,
                y,
                std::min(size, GetScreenWidth() - padding - x),
                std::min(size, GetScreenHeight() - padding - y),
                even ? light : dark
            );
        }
    }
}