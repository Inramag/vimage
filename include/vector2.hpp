#pragma once

#include <raylib.h>

inline Vector2 operator+(Vector2 a, Vector2 b) {
    return {a.x + b.x, a.y + b.y};
}

inline Vector2 operator-(Vector2 a, Vector2 b) {
    return {a.x - b.x, a.y - b.y};
}

inline Vector2 operator*(Vector2 a, float s) {
    return {a.x * s, a.y * s};
}

inline Vector2 operator*(float s, Vector2 a) {
    return {a.x * s, a.y * s};
}

inline Vector2 operator*(Vector2 a, Vector2 b) {
    return {a.x * b.x, a.y * b.y};
}

inline Vector2 operator/(Vector2 a, float s) {
    return {a.x / s, a.y / s};
}

inline Vector2 operator/(Vector2 a, Vector2 b) {
    return {a.x / b.x, a.y / b.y};
}