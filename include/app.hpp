#pragma once

#include <viewer.hpp>

class App {
public:
    int run(int argc, char* argv[]);

private:
    Viewer viewer;
};