#include <app.hpp>

#include <settings.hpp>

#include <filesystem>
namespace fs = std::filesystem;

Viewer App::viewer;

static bool showStatus = false;
static bool showSettings = false;

static Texture checkerboardTexture;
static bool hasCheckerboardImg = false;
    
static Texture paddingTexture;
static bool hasPaddingImg = false;

static bool editingKey = false;

static KeyboardKey getkey(KeyboardKey curr) {
    editingKey = true;
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) break;

        KeyboardKey key = static_cast<KeyboardKey>(GetKeyPressed());
        if (key >= KEY_A && key <= KEY_Z) {
            editingKey = false;
            return key;
        }

        App::draw();
    }
    editingKey = false;
    return curr;
}

int App::run(int argc, char* argv[]) {
    fs::current_path(fs::path(argv[0]).parent_path());
    if (argc != 2) return 1;

    fs::path path = argv[1];

    if (!fs::exists(path) || !fs::is_regular_file(path)) return 2;
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(600, 400, ("vimage > " + path.string()).c_str());
    SetExitKey(KEY_NULL);
    SetWindowMinSize(300, 300);
    
    viewer = Viewer();
    if (!viewer.open(path)) {
        CloseWindow();
        return 3;
    }

    if (fs::exists("assets/checkerboard.png") && fs::is_regular_file("assets/checkerboard.png")) {
        checkerboardTexture = LoadTexture("assets/checkerboard.png");
        hasCheckerboardImg = true;
    }

    if (fs::exists("assets/padding.png") && fs::is_regular_file("assets/padding.png")) {
        paddingTexture = LoadTexture("assets/padding.png");
        hasPaddingImg = true;
    }

    Settings::load();
    viewer.getscale();

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_F1)) showStatus = !showStatus;
        if (IsKeyPressed(KEY_F2)) showSettings = !showSettings;

        draw();
    }

    CloseWindow();

    return 0;
}

void App::draw() {
    BeginDrawing();

    viewer.draw();

    if (showStatus && !showSettings) drawStatus();
    if (showSettings) drawSettings();

    EndDrawing();
}

void App::drawStatus() {
    float pos = 40;
    if (hasCheckerboardImg) DrawTexturePro(
        checkerboardTexture,
        {0, 0, static_cast<float>(checkerboardTexture.width), static_cast<float>(checkerboardTexture.height)},
        {5, 5, 30, 30},
        {0, 0}, 0, Settings::checkerboard() ? WHITE : LIGHTGRAY);
    else pos = 5;
    if (hasPaddingImg) DrawTexturePro(
        paddingTexture,
        {0, 0, static_cast<float>(paddingTexture.width), static_cast<float>(paddingTexture.height)},
        {5, pos, 30, 30},
        {0, 0}, 0, Settings::padding() ? WHITE : LIGHTGRAY);
}

void App::drawSettings() {
    // draw panel
    DrawRectangle(0, 0, 153, 183, BLACK);
    DrawRectangle(0, 0, 152, 182, WHITE);

    // draw render element checkboxes
    Rectangle checkerboard{0, 0, 150, 24};
    DrawRectangleRec(checkerboard, LIGHTGRAY);
    DrawText("Checkerboard", 5, 4, 16, BLACK);
    DrawText(Settings::checkerboard() ? "[x]" : "[ ]", 130, 4, 16, BLACK);

    Rectangle padding{0, 26, 150, 24};
    DrawRectangleRec(padding, LIGHTGRAY);
    DrawText("Padding", 5, 30, 16, BLACK);
    DrawText(Settings::padding() ? "[x]" : "[ ]", 130, 30, 16, BLACK);

    // draw sellector
    DrawLineEx({5, 60}, {145, 60}, 2, BLACK);
    DrawText("Control", 5, 65, 24, BLACK);

    // draw keybinds
    Rectangle key1{0, 96, 150, 24};
    DrawRectangleRec(key1, LIGHTGRAY);
    DrawText("Reset View", 5, 100, 16, BLACK);
    DrawText(Settings::getkey(0) == 0 ? "..." : std::string(1, static_cast<char>(Settings::getkey(0))).c_str(), 130, 100, 16, BLACK);

    Rectangle key2{0, 126, 150, 24};
    DrawRectangleRec(key2, LIGHTGRAY);
    DrawText("Toggle Grid", 5, 130, 16, BLACK);
    DrawText(Settings::getkey(1) == 0 ? "..." : std::string(1, static_cast<char>(Settings::getkey(1))).c_str(), 130, 130, 16, BLACK);
            
    Rectangle key3{0, 156, 150, 24};
    DrawRectangleRec(key3, LIGHTGRAY);
    DrawText("Toggle Padding", 5, 160, 16, BLACK);
    DrawText(Settings::getkey(2) == 0 ? "..." : std::string(1, static_cast<char>(Settings::getkey(2))).c_str(), 130, 160, 16, BLACK);

    // click processing
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 pos = GetMousePosition();

        // checkbox processing
        if (CheckCollisionPointRec(pos, checkerboard)) Settings::setflag(0b00000001, !Settings::checkerboard());
        if (CheckCollisionPointRec(pos, padding)) {
            Settings::setflag(0b00000010, !Settings::padding());
            viewer.getscale();
        }

        // keybinds processing
        if (editingKey) return;
        if (CheckCollisionPointRec(pos, key1)) {
            KeyboardKey curr = static_cast<KeyboardKey>(Settings::getkey(0));
            Settings::setkey(0, 0);
            Settings::setkey(0, getkey(curr));
        }
        if (CheckCollisionPointRec(pos, key2)) {
            KeyboardKey curr = static_cast<KeyboardKey>(Settings::getkey(1));
            Settings::setkey(1, 0);
            Settings::setkey(1, getkey(curr));
        }
        if (CheckCollisionPointRec(pos, key3)) {
            KeyboardKey curr = static_cast<KeyboardKey>(Settings::getkey(2));
            Settings::setkey(2, 0);
            Settings::setkey(2, getkey(curr));
        }
    }

    if (IsKeyPressed(KEY_ESCAPE)) showSettings = false;
}