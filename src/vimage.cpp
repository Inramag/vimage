#include <vimage.hpp>

#include <stb/stb_image.h>
#include <fstream>

#include <error.hpp>

#include <algorithm>

void VImage::get(Texture& texture) {
    texture = LoadTextureFromImage({
        frames[0].pixels.data(),
        width, height,
        1,
        PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    });
}

VImage VImage::load(const std::filesystem::path& path) {
    VImage img{};
    
    std::string ext = path.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) { return std::tolower(c); });

    if (ext == ".png") img.format = Format::png;
    else if (ext == ".jpg" || ext == ".jpeg") img.format = Format::jpg;
    else error("Unsupported image format.");

    std::ifstream file(path, std::ios::binary);

    std::vector<unsigned char> bytes(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    file.close();

    int w = 0, h = 0, comp = 0;
    unsigned char* raw = stbi_load_from_memory(bytes.data(), static_cast<int>(bytes.size()), &w, &h, &comp, 4);
        
    img.frames.push_back(Frame{ std::vector<unsigned char>(raw, raw + (w * h * 4)) });
    stbi_image_free(raw);

    img.width = w;
    img.height = h;

    img.hasalpha = (comp == 4 || comp == 2);

    return img;
}