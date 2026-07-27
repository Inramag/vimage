#include <vimage.hpp>

#include <stb/stb_image.h>

#include <algorithm>

#include <fstream>

VImage VImage::load(const std::filesystem::path& path) {
    std::string ext = path.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) { return std::tolower(c); });

    VImage img;

    if (ext == ".png") img.format = VFormat::png;
    else if (ext == ".jpg" || ext == ".jpeg") img.format = VFormat::jpg;
    else return img;

    std::ifstream file(path, std::ios::binary);

    std::vector<unsigned char> bytes(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    file.close();

    int w = 0, h = 0, comp = 0;
    unsigned char* raw = stbi_load_from_memory(bytes.data(), static_cast<int>(bytes.size()), &w, &h, &comp, 4);
        
    img.frames.push_back(VFrame{ std::vector<unsigned char>(raw, raw + (w * h * 4)) });
    stbi_image_free(raw);

    img.width = w;
    img.height = h;

    img.hasalpha = (comp == 4 || comp == 2);

    return img;
}