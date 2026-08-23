#include <iostream>
#include <ui.hpp>

#include <settings.hpp>

#include <vimage.hpp>
#include <viewer.hpp>

#include <raylib.h>
#include <stb/stb_image.h>

#include <string>
#include <filesystem>

static Texture checkerboard_texture{}, padding_texture{};
static bool has_checkerboard = 0, has_padding = 0;

static bool show_status = 0, show_settings = 0;

static bool editingKey = 0;

static KeyboardKey getkey(KeyboardKey curr) {
    editingKey = true;
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) break;

        KeyboardKey key = static_cast<KeyboardKey>(GetKeyPressed());
        if (key >= KEY_A && key <= KEY_Z) {
            editingKey = false;
            return key;
        }
    }
    editingKey = false;
    return curr;
}

static bool load_asset(const std::filesystem::path& asset, Texture& texture) {
    const std::filesystem::path path = settings::program / "assets" / asset;
    if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path)) {
        texture = VImage::load(path).frames[0].texture;
        std::cout << "[Assets] load asset " + path.string() << ".\n";
        return true;
    }
    std::cout << "[Assets] asset " + path.string() + " no exist.\n";
    return false;
}

void ui::load() {
    has_checkerboard = load_asset("checkerboard.png", checkerboard_texture);
    has_padding = load_asset("padding.png", padding_texture);
}

void ui::toggle_status() {
    show_status = !show_status;
    viewer::getscale();
}
void ui::toggle_settings() {
    show_settings = !show_settings;
    viewer::getscale();
}

static void draw_status() {
    float pos = 40;
    if (has_checkerboard) DrawTexturePro(
        checkerboard_texture,
        {0, 0, static_cast<float>(checkerboard_texture.width), static_cast<float>(checkerboard_texture.height)},
        {5, 5, 30, 30},
        {0, 0}, 0, settings::checkerboard() ? WHITE : LIGHTGRAY);
    else pos = 5;
    if (has_padding) DrawTexturePro(
        padding_texture,
        {0, 0, static_cast<float>(padding_texture.width), static_cast<float>(padding_texture.height)},
        {5, pos, 30, 30},
        {0, 0}, 0, settings::padding() ? WHITE : LIGHTGRAY);
}

static void draw_settings() {
    // draw panel
    DrawRectangle(0, 0, 153, 183, BLACK);
    DrawRectangle(0, 0, 152, 182, WHITE);

    // draw render element checkboxes
    Rectangle checkerboard{0, 0, 150, 24};
    DrawRectangleRec(checkerboard, LIGHTGRAY);
    DrawText("Checkerboard", 5, 4, 16, BLACK);
    DrawText(settings::checkerboard() ? "[x]" : "[ ]", 130, 4, 16, BLACK);

    Rectangle padding{0, 26, 150, 24};
    DrawRectangleRec(padding, LIGHTGRAY);
    DrawText("Padding", 5, 30, 16, BLACK);
    DrawText(settings::padding() ? "[x]" : "[ ]", 130, 30, 16, BLACK);

    // draw sellector
    DrawLineEx({5, 60}, {145, 60}, 2, BLACK);
    DrawText("Control", 5, 65, 24, BLACK);

    // draw keybinds
    Rectangle key1{0, 96, 150, 24};
    DrawRectangleRec(key1, LIGHTGRAY);
    DrawText("Reset View", 5, 100, 16, BLACK);
    DrawText(settings::getkey(0) == 0 ? "..." : std::string(1, static_cast<char>(settings::getkey(0))).c_str(), 130, 100, 16, BLACK);

    Rectangle key2{0, 126, 150, 24};
    DrawRectangleRec(key2, LIGHTGRAY);
    DrawText("Toggle Grid", 5, 130, 16, BLACK);
    DrawText(settings::getkey(1) == 0 ? "..." : std::string(1, static_cast<char>(settings::getkey(1))).c_str(), 130, 130, 16, BLACK);
            
    Rectangle key3{0, 156, 150, 24};
    DrawRectangleRec(key3, LIGHTGRAY);
    DrawText("Toggle Padding", 5, 160, 16, BLACK);
    DrawText(settings::getkey(2) == 0 ? "..." : std::string(1, static_cast<char>(settings::getkey(2))).c_str(), 130, 160, 16, BLACK);

    // click processing
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 pos = GetMousePosition();

        // checkbox processing
        if (CheckCollisionPointRec(pos, checkerboard)) settings::setflag(0b00000001, !settings::checkerboard());
        if (CheckCollisionPointRec(pos, padding)) settings::setflag(0b00000010, !settings::padding());

        // keybinds processing
        if (editingKey) return;
        if (CheckCollisionPointRec(pos, key1)) {
            KeyboardKey curr = static_cast<KeyboardKey>(settings::getkey(0));
            settings::setkey(0, 0);
            settings::setkey(0, getkey(curr));
        }
        if (CheckCollisionPointRec(pos, key2)) {
            KeyboardKey curr = static_cast<KeyboardKey>(settings::getkey(1));
            settings::setkey(1, 0);
            settings::setkey(1, getkey(curr));
        }
        if (CheckCollisionPointRec(pos, key3)) {
            KeyboardKey curr = static_cast<KeyboardKey>(settings::getkey(2));
            settings::setkey(2, 0);
            settings::setkey(2, getkey(curr));
        }
    }

    if (IsKeyPressed(KEY_ESCAPE)) show_settings = false;
}

void ui::draw() {
    if (show_settings) draw_settings();
    else if (show_status) draw_status();
}
