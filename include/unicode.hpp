#pragma once

#include <string>

namespace unicode {
    std::string to_utf8(std::wstring_view wstr);
    std::wstring to_wide(std::string_view str);
}