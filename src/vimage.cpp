#include <cstdlib>
#include <vimage.hpp>

#include <stb/stb_image.h>
#include <fstream>

#include <error.hpp>

VImage VImage::load(const std::filesystem::path& path) {
    VImage img{};
    
    std::string ext = path.extension().string();

    for (char& c : ext) c = std::tolower(c);

    if (ext == ".png") img.format = Format::png;
    else if (ext == ".jpg" || ext == ".jpeg") img.format = Format::jpg;
    else if (ext == ".gif") img.format = Format::gif;
    else error("Unsupported image format.");

    std::ifstream file(path, std::ios::binary);

    std::vector<unsigned char> bytes(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    file.close();

    int* delays;
    int w = 0, h = 0, c = 0, comp = 0;
    unsigned char* raw = img.format == Format::gif ?
        stbi_load_gif_from_memory(bytes.data(), static_cast<int>(bytes.size()), &delays, &w, &h, &c, &comp, 4) :
        stbi_load_from_memory(bytes.data(), static_cast<int>(bytes.size()), &w, &h, &comp, 4);

    size_t s = static_cast<size_t>(w) * h * 4;
    if (img.format == Format::gif) {
        for (int i = 0; i < c; i++)
            img.frames.push_back({std::vector<unsigned char>(raw + i * s, raw + (i + 1) * s), w, h, delays[i]});
        free(delays);
    } else img.frames.push_back({std::vector<unsigned char>(raw, raw + s), w, h});

    stbi_image_free(raw);

    img.width = w;
    img.height = h;

    img.hasalpha = (comp == 4 || comp == 2);
    
    return img;
}
