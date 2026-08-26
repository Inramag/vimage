#include <array>
#include <utility>
#include <vimage.hpp>

#include <stb/stb_image.h>
#include <fstream>

#include <error.hpp>

std::array<std::pair<std::string, Format>, 4> magics {
    std::pair {"\x89PNG\r\n\x1a\n", Format::png},
    std::pair {"\xFF\xD8\xFF",      Format::jpg},
    std::pair {"GIF87a",            Format::gif},
    std::pair {"GIF89a",            Format::gif}
};

VImage VImage::load(const std::filesystem::path& path) {
    VImage img{};

    // determine the image format from its file magic.    
    std::ifstream file(path, std::ios::binary);

    bool iscorrect = false;

    for (const auto& magic : magics) {
        std::string fmagic(magic.first.length(), '\0');

        file.read(fmagic.data(), magic.first.length());

        if (file.gcount() == magic.first.length() && fmagic == magic.first) {
            iscorrect = true;
            img.format = magic.second;
        }

        file.seekg(0);

        if (iscorrect) break;
    }
    
    if (!iscorrect) error("Unsupported image format.");

    // read the entire file into memory for stb_image.
    std::vector<unsigned char> bytes(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    file.close();

    int* delays;
    int w = 0, h = 0, c = 0, comp = 0;

    // GIFs are decoded into a contiguous array containing all frames.
    unsigned char* raw = img.format == Format::gif ?
        stbi_load_gif_from_memory(bytes.data(), static_cast<int>(bytes.size()), &delays, &w, &h, &c, &comp, 4) :
        stbi_load_from_memory(bytes.data(), static_cast<int>(bytes.size()), &w, &h, &comp, 4);

    size_t s = static_cast<size_t>(w) * h * 4;
    if (img.format == Format::gif) {
        for (int i = 0; i < c; i++)
            img.frames.push_back({std::vector<unsigned char>(raw + i * s, raw + (i + 1) * s), w, h, delays[i]});

        // delay is allocated by stb_image's memory allocator.
        free(delays);
    } else img.frames.push_back({std::vector<unsigned char>(raw, raw + s), w, h});

    stbi_image_free(raw);

    img.width = w;
    img.height = h;

    img.hasalpha = (comp == 4 || comp == 2);
    
    return img;
}
