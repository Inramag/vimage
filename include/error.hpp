#pragma once

enum class ErrorCode {
    None = 0,
    NoImage,
    FileNotFound,
    UnsupportedFormat
};

void error(ErrorCode code);