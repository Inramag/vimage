#include <windows.h>
#include <winuser.h>

#include <filesystem>
namespace fs = std::filesystem;

#include <algorithm>

#include <unordered_set>
#include <string_view>


void error(const std::wstring_view& text) {
    MessageBoxW(
        nullptr,
        text.data(),
        L"vimage",
        MB_OK | MB_ICONERROR
    );
}

static const std::unordered_set<std::string> formats = {
    ".png"
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        error(L"No image file specified.");
        return 1;
    }

    fs::path path = argv[1];

    if (!fs::exists(path) || !fs::is_regular_file(path)) {
        error(L"File not found.");
        return 1;
    }

    std::string ext = path.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) { return std::tolower(c); });

    if (formats.find(ext) == formats.end()) {
        error(L"Unsupported image format.");
        return 1;
    }

    return 0;
}