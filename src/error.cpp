#include "error.hpp"

#include <windows.h>

#include <unordered_map>
#include <string_view>

static const std::unordered_map<ErrorCode, std::wstring_view> errors {
    {ErrorCode::NoImage, L"No image file specified."},
    {ErrorCode::FileNotFound, L"File not found."},
    {ErrorCode::UnsupportedFormat, L"Unsupported image format."}
};

void error(ErrorCode code) {
    MessageBoxW(
        nullptr,
        errors.at(code).data(),
        L"vimage",
        MB_OK | MB_ICONERROR
    );
}