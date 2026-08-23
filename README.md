# vimage

A lightweight and fast image viewer for Windows.

## Screenshots

| Windowed | Status Indicators |
|-|-|
|<img src="https://github.com/user-attachments/assets/a81f9fdd-b91a-4309-8ada-f5a4fdfe8077" />|<img src="https://github.com/user-attachments/assets/f828e6a7-c1fc-47a1-afad-53a04a72d91e" />|

| Settings Menu | Padding Disabled |
|-|-|
|<img src="https://github.com/user-attachments/assets/e10a5636-f6fc-4e56-b8d8-2c5d031fd954" />|<img src="https://github.com/user-attachments/assets/b3f0bb86-3235-4e5a-8550-af5040c15977" />|

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
- GIF animation
- Manual GIF frame switching

## Supported Formats

- PNG
- JPEG (.jpg, .jpeg)
- GIF

## Controls

| Action | Input |
|-|-|
| Toggle Status Indicators | F1 |
| Toggle Settings Menu | F2 |
| Zoom | Ctrl + Mouse Wheel |
| Pan | Mouse Wheel |
| Reset View | R *(configurable)* |
| Toggle Checkerboard | G *(configurable)* |
| Toggle Padding | P *(configurable)* |
| Play / Pause GIF | Space |
| Previous GIF Frame | Left Arrow |
| Next GIF Frame | Right Arrow |

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
