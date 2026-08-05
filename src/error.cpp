#include <error.hpp>

#include <unicode.hpp>

#include <windows.h>

void error(std::string_view msg) {
    MessageBoxW(
        nullptr,
        unicode::to_wide(msg).data(),
        L"vimage",
        MB_OK | MB_ICONERROR
    );
    exit(0);
}