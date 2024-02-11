#include "image.h"
#include <iostream>
#include <fstream>
#include <utility>

Color::Color() : r_(0), g_(0), b_(0){};

Color::Color(float r, float g, float b) : r_(r), g_(g), b_(b) {
}

Color::Color(const Color &other) : r_(other.r_), g_(other.g_), b_(other.b_){};

Color::~Color() {
}

Color Color::operator=(Color col) {
    this->r_ = col.r_;
    this->g_ = col.g_;
    this->b_ = col.b_;
    return *this;
}

bool Color::operator==(Color col) const {
    if (r_ == col.r_ && b_ == col.b_ && g_ == col.g_) {
        return true;
    }
    return false;
}

Image::Image(int width, int height) {
    width_ = width;
    height_ = height;
    Color nul(0, 0, 0);
    pixels_.resize(height);
    for (size_t i = 0; i < height; ++i) {
        pixels_[i].resize(width);
        for (size_t j = 0; j < width; ++j) {
            pixels_[i][j] = nul;
        }
    }
};

Image::Image(int width, int height, std::vector<std::vector<Color>> colors)
    : width_(width), height_(height), pixels_(std::move(colors)){};

Image::~Image() = default;

Color Image::GetColor(int x, int y) const {
    return pixels_[y][x];
}

void Image::SetColor(const Color &color, int x, int y) {
    pixels_[y][x].r_ = color.r_;
    pixels_[y][x].g_ = color.g_;
    pixels_[y][x].b_ = color.b_;
}

int Image::GetWidth() const {
    return this->width_;
}

int Image::GetHeight() const {
    return this->height_;
}

Image Image::operator=(const Image &other) {
    this->width_ = other.width_;
    this->height_ = other.height_;
    this->pixels_ = other.pixels_;
    return *this;
}

bool Image::operator==(const Image &other) const {
    if (width_ != other.width_ || height_ != other.height_) {
        return false;
    }
    return pixels_ == other.pixels_;
}

void Image::Read(const char *path) {
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        std::cout << "File could not be opened" << std::endl;
        return;
    }
    const int file_header_size = 14;         // DISABLE_NOLINT
    const int information_header_size = 40;  // DISABLE_NOLINT
    unsigned char file_header[file_header_size];
    f.read(reinterpret_cast<char *>(file_header), file_header_size);
    if (file_header[0] != 'B' || file_header[1] != 'M') {
        std::cout << "The specified path is mot a bmp image" << std::endl;
        f.close();
        return;
    }
    unsigned char information_header[information_header_size];
    f.read(reinterpret_cast<char *>(information_header), information_header_size);
    // const int file_size = file_header[2] + (file_header[3] << 8) + (file_header[4] << 16) + (file_header[5] << 24);
    width_ = information_header[4] + (information_header[5] << 8) + (information_header[6] << 16) +    // DISABLE_NOLINT
             (information_header[7] << 24);                                                            // DISABLE_NOLINT
    height_ = information_header[8] + (information_header[9] << 8) + (information_header[10] << 16) +  // DISABLE_NOLINT
              (information_header[11] << 24);                                                          // DISABLE_NOLINT
    Color help(0, 0, 0);
    pixels_.resize(height_);
    for (size_t i = 0; i < height_; ++i) {
        pixels_[i].resize(width_);
        for (size_t j = 0; j < width_; ++j) {
            pixels_[i][j] = help;
        }
    }
    const int padding_amount = (4 - (width_ * 3) % 4) % 4;  // DISABLE_NOLINT
    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            unsigned char color[3];                                    // DISABLE_NOLINT
            f.read(reinterpret_cast<char *>(color), 3);                // DISABLE_NOLINT
            pixels_[y][x].r_ = static_cast<float>(color[2]) / 255.0f;  // DISABLE_NOLINT
            pixels_[y][x].g_ = static_cast<float>(color[1]) / 255.0f;  // DISABLE_NOLINT
            pixels_[y][x].b_ = static_cast<float>(color[0]) / 255.0f;  // DISABLE_NOLINT
        }
        f.ignore(padding_amount);
    }
    f.close();
    // std::cout << "File read" << std::endl;  // return *this;
};

void Image::Export(const char *path) const {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);
    if (!f.is_open()) {
        std::cout << "File could not be opened\n";
        return;
    }
    unsigned char bmp_pad[3] = {0, 0, 0};                   // DISABLE_NOLINT
    const int padding_amount = (4 - (width_ * 3) % 4) % 4;  // DISABLE_NOLINT
    const int file_header_size = 14;                        // DISABLE_NOLINT
    const int information_header_size = 40;                 // DISABLE_NOLINT
    const int file_size =
        file_header_size + information_header_size + width_ * height_ * 3 + padding_amount * width_;  // DISABLE_NOLINT
    unsigned char file_header[file_header_size];
    file_header[0] = 'B';
    file_header[1] = 'M';
    file_header[2] = file_size;                                    // DISABLE_NOLINT
    file_header[3] = file_size >> 8;                               // DISABLE_NOLINT
    file_header[4] = file_size >> 16;                              // DISABLE_NOLINT
    file_header[5] = file_size >> 24;                              // DISABLE_NOLINT
    file_header[6] = 0;                                            // DISABLE_NOLINT
    file_header[7] = 0;                                            // DISABLE_NOLINT
    file_header[8] = 0;                                            // DISABLE_NOLINT
    file_header[9] = 0;                                            // DISABLE_NOLINT
    file_header[10] = file_header_size + information_header_size;  // DISABLE_NOLINT
    file_header[11] = 0;                                           // DISABLE_NOLINT
    file_header[12] = 0;                                           // DISABLE_NOLINT
    file_header[13] = 0;                                           // DISABLE_NOLINT
    unsigned char information_header[information_header_size];
    information_header[0] = information_header_size;
    information_header[1] = 0;               // DISABLE _NOLINT
    information_header[2] = 0;               // DISABLE _NOLINT
    information_header[3] = 0;               // DISABLE _NOLINT
    information_header[4] = width_;          // DISABLE _NOLINT
    information_header[5] = width_ >> 8;     // DISABLE _NOLINT
    information_header[6] = width_ >> 16;    // DISABLE _NOLINT
    information_header[7] = width_ >> 24;    // DISABLE _NOLINT
    information_header[8] = height_;         // DISABLE _NOLINT
    information_header[9] = height_ >> 8;    // DISABLE _NOLINT
    information_header[10] = height_ >> 16;  // DISABLE _NOLINT
    information_header[11] = height_ >> 24;  // DISABLE _NOLINT
    information_header[12] = 1;              // DISABLE _NOLINT
    information_header[13] = 0;              // DISABLE _NOLINT
    information_header[14] = 24;             // DISABLE _NOLINT
    information_header[15] = 0;              // DISABLE _NOLINT
    information_header[16] = 0;              // DISABLE _NOLINT
    information_header[17] = 0;              // DISABLE _NOLINT
    information_header[18] = 0;              // DISABLE _NOLINT
    information_header[19] = 0;              // DISABLE _NOLINT
    information_header[20] = 0;              // DISABLE _NOLINT
    information_header[21] = 0;              // DISABLE _NOLINT
    information_header[22] = 0;              // DISABLE _NOLINT
    information_header[23] = 0;              // DISABLE _NOLINT
    information_header[24] = 0;              // DISABLE _NOLINT
    information_header[25] = 0;              // DISABLE _NOLINT
    information_header[26] = 0;              // DISABLE _NOLINT
    information_header[27] = 0;              // DISABLE _NOLINT
    information_header[28] = 0;              // DISABLE _NOLINT
    information_header[29] = 0;              // DISABLE _NOLINT
    information_header[30] = 0;              // DISABLE _NOLINT
    information_header[31] = 0;              // DISABLE _NOLINT
    information_header[32] = 0;              // DISABLE _NOLINT
    information_header[33] = 0;              // DISABLE _NOLINT
    information_header[34] = 0;              // DISABLE _NOLINT
    information_header[35] = 0;              // DISABLE _NOLINT
    information_header[36] = 0;              // DISABLE _NOLINT
    information_header[37] = 0;              // DISABLE _NOLINT
    information_header[38] = 0;              // DISABLE _NOLINT
    information_header[39] = 0;              // DISABLE _NOLINT

    f.write(reinterpret_cast<char *>(file_header), file_header_size);
    f.write(reinterpret_cast<char *>(information_header), information_header_size);
    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            unsigned char r = static_cast<unsigned char>(GetColor(x, y).r_ * 255.0f);  // DISABLE_NOLINT
            unsigned char g = static_cast<unsigned char>(GetColor(x, y).g_ * 255.0f);  // DISABLE_NOLINT
            unsigned char b = static_cast<unsigned char>(GetColor(x, y).b_ * 255.0f);  // DISABLE_NOLINT
            unsigned char color[] = {b, g, r};
            f.write(reinterpret_cast<char *>(color), 3);  // DISABLE_NOLINT
        }
        f.write(reinterpret_cast<char *>(bmp_pad), padding_amount);
    }
    f.close();
}
Image::Image() {
}
