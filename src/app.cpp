#include <app.hpp>

#include <filesystem>
namespace fs = std::filesystem;

int App::run(int argc, char* argv[]) {
    if (argc != 2) return 1;

    fs::path path = argv[1];

    if (!fs::exists(path) || !fs::is_regular_file(path)) return 2;
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(600, 400, ("vimage > " + path.string()).c_str());
    SetWindowMinSize(300, 300);
    
    viewer = Viewer();
    if (!viewer.open(path)) {
        CloseWindow();
        return 3;
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        viewer.draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}