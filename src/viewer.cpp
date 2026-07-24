#include <viewer.hpp>

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
    ClearBackground(BLACK);

    DrawTextureEx(texture, position, 0, scale, WHITE);
}

void Viewer::updateTransform() {
    scale = std::min(
        static_cast<float>(GetScreenWidth()) / texture.width,
        static_cast<float>(GetScreenHeight()) / texture.height
    ) * 0.95f;

    position = {
        (GetScreenWidth() - texture.width * scale) / 2.0f,
        (GetScreenHeight() - texture.height * scale) / 2.0f
    };
}