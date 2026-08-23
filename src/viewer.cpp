#include <viewer.hpp>

#include <settings.hpp>
#include <vector2.hpp>

#include <cmath>
#include <algorithm>

static VImage img;
static Texture texture;

static int frame = 0;
static bool isgif = false;
static bool plays = false;
static std::chrono::steady_clock::time_point currtime;

static float scale;
static float zoom = 1;
static Vector2 ssize{};
static Vector2 offset{};

static const int padding = 20;

// return the  position at which the image should be drawn.
Vector2 getpos() {
    return {
        (GetScreenWidth() - ssize.x) / 2.0f,
        (GetScreenHeight() - ssize.y) / 2.0f
    };
}

// handle window resizing, zooming and image movement.
void amended() {
    if (IsWindowResized()) viewer::getscale();

    float wheel = GetMouseWheelMove();

    if (wheel == 0) return;

    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        Vector2 mouse = GetMousePosition();

        // preserve the point under the cursor while zooming.
        Vector2 relative = (mouse - getpos() - offset) / ssize;

        zoom = std::clamp(zoom * std::pow(1.1f, wheel), 0.5f, 200.0f);

        viewer::getscale();

        offset = mouse - getpos() - relative * ssize;
    } else {
        float val = wheel * 20;

        Vector2 center = {
            GetScreenWidth() / 2.0f,
            GetScreenHeight() / 2.0f
        };
    
        Vector2 pos = getpos();

        // shift + mouse wheel moves the image horizontally.
        if (IsKeyDown(KEY_LEFT_SHIFT))
            offset.x = std::clamp(
                offset.x + val,
                center.x - pos.x - ssize.x,
                center.x - pos.x);
        else offset.y = std::clamp(offset.y + val,
            center.y - pos.y - ssize.y,
            center.y - pos.y);
    }
}

// draw the image background and checkerboard for transparent images.
void grid() {
    Vector2 pos = getpos() + offset;
    
    DrawRectangle(
        static_cast<int>(pos.x) - 1,
        static_cast<int>(pos.y) - 1,
        static_cast<int>(ssize.x) + 2,
        static_cast<int>(ssize.y) + 2,
        BLACK
    );

    if (!img.hasalpha) return;

    constexpr int size = 50;

    int left   = static_cast<int>(pos.x);
    int top    = static_cast<int>(pos.y);
    int right  = left + static_cast<int>(ssize.x);
    int bottom = top + static_cast<int>(ssize.y);

    int y = static_cast<int>(pos.y);
    int startY = y < 0 ? -((-y) % size) : y;

    int endY = std::min(bottom, GetScreenHeight());

    int x = static_cast<int>(pos.x);
    int startX = x < 0 ? -((-x) % size) : x;

    int endX = std::min(right, GetScreenWidth());

    DrawRectangle(startX, startY, endX - startX, endY - startY, {255, 255, 255, 255});
    
    if (!settings::checkerboard()) return;

    bool evenRow = (((left - startX) / size + (top - startY) / size) & 1) == 0;
    
    for (int y = startY; y < endY; y += size) {
        bool even = evenRow;
        for (int x = startX; x < endX; x += size) {
            if (even) DrawRectangle(x, y, std::min(size, endX - x), std::min(size, endY - y), {224, 224, 224, 255});

            even = !even;
        }
        
        evenRow = !evenRow;
    }
}

// select a frame and reset its animation timer.
void setframe(int n) {
    frame = n;
    texture = img.frames[frame].texture;
    
    currtime = std::chrono::steady_clock::now();

    viewer::getscale();
}

// advance the gif animation when the current frame has expired.
void animate() {
    if (!isgif || !plays) return;

    auto now = std::chrono::steady_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - currtime).count();

    if (elapsed >= img.frames[frame].delay) setframe((frame + 1) % img.frames.size());
}

// draw the current frame.
void _draw() {
    ClearBackground({240, 240, 240, 255});

    grid();

    Rectangle src = {0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height)};

    Vector2 pos = getpos() + offset;

    Rectangle dst = {pos.x, pos.y, ssize.x, ssize.y};

    DrawTexturePro(texture, src, dst, {0, 0}, 0.0f, WHITE);
}

void viewer::load(const VImage& vimg) {
    img = std::move(vimg);

    // create GPU textures after the window has been initialized.
    for (Frame& frame : img.frames) frame.texture = LoadTextureFromImage({frame.pixels.data(), img.width, img.height, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8});

    texture = img.frames[0].texture;
    isgif = img.format == Format::gif;
    
    getscale();

    _draw();
}

void viewer::draw() {
    // reset view.
    if (IsKeyPressed(settings::config.keys[0])) {
        offset = {0, 0};
        zoom = 1;
        getscale();
    }

    // toggle checkerboard.
    if (IsKeyPressed(settings::config.keys[1])) settings::setflag(0b00000001, !settings::checkerboard());

    // toggle padding.
    if (IsKeyPressed(settings::config.keys[2])) {
        settings::setflag(0b00000010, !settings::padding());
        getscale();
    }
    
    if (IsKeyPressed(KEY_F11)) ToggleFullscreen();

    if (isgif) {
        // start or pause animation.
        if (IsKeyPressed(KEY_SPACE)) {
            plays = !plays;
            currtime = std::chrono::steady_clock::now();
        }

        // manually switch frames.
        if (IsKeyPressed(KEY_LEFT)) setframe((frame + img.frames.size() - 1) % img.frames.size());
        if (IsKeyPressed(KEY_RIGHT)) setframe((frame + 1) % img.frames.size());
    }

    animate();
    
    amended();
    _draw();
}

void viewer::getscale() {
    int pad = settings::padding() ? padding : 0;
    scale = std::min(
        static_cast<float>(GetScreenWidth() - pad * 2) / texture.width,
        static_cast<float>(GetScreenHeight() - pad * 2) / texture.height
    );
    float s = scale * zoom;
    ssize = {
        std::round(texture.width * s),
        std::round(texture.height * s)
    };
}
