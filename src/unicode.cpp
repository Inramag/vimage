#include <unicode.hpp>

#include <stringapiset.h>

std::string unicode::to_utf8(std::wstring_view wstr) {
    if (wstr.empty()) return {};

    int size = WideCharToMultiByte(
        CP_UTF8, 0,
        wstr.data(), static_cast<int>(wstr.size()),
        nullptr, 0,
        nullptr, nullptr);

    if (size == 0) return {};

    std::string res(size, '\0');

    WideCharToMultiByte(
        CP_UTF8, 0,
        wstr.data(), static_cast<int>(wstr.size()),
        res.data(), size,
        nullptr, nullptr);

    return res;
}

std::wstring unicode::to_wide(std::string_view str) {
    if (str.empty()) return {};

    int size = MultiByteToWideChar(
        CP_UTF8, MB_ERR_INVALID_CHARS,
        str.data(), static_cast<int>(str.size()),
        nullptr, 0);

    if (size == 0) return {};

    std::wstring res(size, L'\0');

    MultiByteToWideChar(
        CP_UTF8, 0,
        str.data(), static_cast<int>(str.size()),
        res.data(), size);

    return res;
}