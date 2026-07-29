#pragma once

#include <viewer.hpp>

class App {
public:
    int run(int argc, char* argv[]);

    static void draw();

    static void drawStatus();
    static void drawSettings();

private:
    static Viewer viewer;
};