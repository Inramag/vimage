#include <fileapi.h>
#include <winerror.h>
#include <errhandlingapi.h>

#include <error.hpp>
#include <unicode.hpp>
#include <settings.hpp>

#include <ui.hpp>
#include <vimage.hpp>
#include <viewer.hpp>

int wmain(int argc, wchar_t* argv[]) {
    if (argc == 1) error("No file path.");
    if (argc > 2) error("Only one argument.");

    const std::filesystem::path path = argv[1];

    if (GetFileAttributesW(path.c_str()) == INVALID_FILE_ATTRIBUTES) {
        switch (GetLastError()) {
        case ERROR_INVALID_NAME:
            error("Invalid path.");
            break;
        
        case ERROR_FILE_NOT_FOUND:
        case ERROR_PATH_NOT_FOUND:
            error("File not found.");
            break;

        case ERROR_ACCESS_DENIED:
            error("Access denied.");
            break;
        
        case ERROR_SHARING_VIOLATION:
            error("File is being used by anouther process.");
            break;

        default:
            error("Unknown error.");
            break;
        }
    }

    VImage img = VImage::load(path);

    settings::program = std::filesystem::path(argv[0]).parent_path();
    settings::load();

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(200, 200, unicode::to_utf8(L"vimage > " + path.wstring()).c_str());
    SetExitKey(KEY_NULL);
    SetWindowMinSize(200, 200);

    viewer::load(img);
    ui::load();

    while(!WindowShouldClose()) {
        if (IsKeyPressed(KEY_F1)) ui::toggle_status();
        if (IsKeyPressed(KEY_F2)) ui::toggle_settings();

        BeginDrawing();

        viewer::draw();
        ui::draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
