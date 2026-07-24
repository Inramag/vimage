#include <error.hpp>

#include <app.hpp>

int main(int argc, char* argv[]) {
    App app{};
    ErrorCode code = static_cast<ErrorCode>(app.run(argc, argv));

    if (code != ErrorCode::None) error(code);
    return 0;
}