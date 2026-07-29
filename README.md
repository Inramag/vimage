# vimage

A lightweight and fast image viewer for Windows.

## Features

- Fast startup
- Lightweight
- Automatic image fitting
- Mouse wheel zoom
- Mouse panning
- Transparency checkerboard
- Optional image padding
- Fullscreen mode
- Configurable keyboard shortcuts
- Persistent settings
- Window resizing support

## Supported Formats

- PNG
- JPEG (.jpg, .jpeg)

## Controls

| Action | Input |
|--------|-------|
| Toggle Status Indicators | F1 |
| Toggle Settings Menu | F2 |
| Zoom | Ctrl + Mouse Wheel |
| Pan | Mouse Wheel |
| Reset View | R *(configurable)* |
| Toggle Checkerboard | G *(configurable)* |
| Toggle Padding | P *(configurable)* |

## Configuration

Settings are stored in `conf.bin` and include:

- Transparency checkerboard
- Image padding
- Configurable keyboard shortcuts

## Building

```bash
cmake -B build
cmake --build build
```

## Dependencies

- raylib
- stb_image