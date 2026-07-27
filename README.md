# vimage

A lightweight and fast image viewer for Windows.

## Features

- Fast startup
- Lightweight
- Automatic image fitting
- Mouse wheel zoom
- Pan with the mouse wheel
- Transparency checkerboard
- Window resizing support
- Keyboard shortcuts

## Supported Formats

- PNG
- JPEG (.jpg, .jpeg)

## Controls

| Action | Input |
|--------|-------|
| Zoom | Ctrl + Mouse Wheel |
| Pan | Mouse Wheel |
| Reset View | R |
| Toggle Checkerboard | G |
| Toggle Padding | P |

## Building

```bash
cmake -B build
cmake --build build
```

## Dependencies

- raylib
- stb_image