#include <app.hpp>

#include <settings.hpp>

#include <filesystem>
namespace fs = std::filesystem;

static bool isf2 = false;

int App::run(int argc, char* argv[]) {
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

    while (!WindowShouldClose()) {
        BeginDrawing();
        viewer.draw();

        if (IsKeyPressed(KEY_F2)) isf2 = !isf2;
        if (isf2) {
            DrawRectangle(0, 0, 153, 53, BLACK);
            DrawRectangle(0, 0, 152, 52, WHITE);

            Rectangle checkerboard{0, 0, 150, 24};
            DrawRectangleRec(checkerboard, LIGHTGRAY);
            DrawText("Checkerboard", 5, 4, 18, BLACK);
            DrawText(Settings::checkerboard() ? "[x]" : "[ ]", 130, 4, 18, BLACK);
            Rectangle padding{0, 26, 150, 24};
            DrawRectangleRec(padding, LIGHTGRAY);
            DrawText("Padding", 5, 30, 18, BLACK);
            DrawText(Settings::padding() ? "[x]" : "[ ]", 130, 30, 18, BLACK);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 pos = GetMousePosition();

                if (CheckCollisionPointRec(pos, checkerboard)) Settings::set(0b00000001, !Settings::checkerboard());
                if (CheckCollisionPointRec(pos, padding)) {
                    Settings::set(0b00000010, !Settings::padding());
                    viewer.getscale();
                }
            }

            if (IsKeyPressed(KEY_ESCAPE)) isf2 = false;
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}