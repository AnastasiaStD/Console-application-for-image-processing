
#include "sharpening.h"
#include <cmath>
#include <vector>
#include <algorithm>

void FilterSR(Image& copy) {
    float a = 5;  // DISABLE _NOLINT
    int new_h = copy.height_ + 2;
    int new_w = copy.width_ + 2;
    std::vector<std::vector<Color>> vec(new_h);
    for (size_t i = 0; i < new_h; ++i) {
        vec[i].resize(new_w);
        for (size_t j = 0; j < new_w; ++j) {
            if (i != 0 && j != 0 && j != (new_w - 1) && i != (new_h - 1)) {
                vec[i][j] = copy.pixels_[i - 1][j - 1];
            } else if (i == 0 && j != 0 && j != new_w - 1) {
                vec[i][j] = copy.pixels_[i][j - 1];
            } else if (j == 0 && i != 0 && i != new_h - 1) {
                vec[i][j] = copy.pixels_[i - 1][j];
            } else if (i == (new_h - 1) && j != 0 && j != (new_w - 1)) {
                vec[i][j] = copy.pixels_[i - 2][j - 1];
            } else if (j == (new_w - 1) && i != (new_h - 1) && i != 0) {
                vec[i][j] = copy.pixels_[i - 1][j - 2];
            }
        }
    }

    Image new_im = Image(copy.width_, copy.height_);

    for (size_t i = 0; i < copy.height_; ++i) {
        for (size_t j = 0; j < copy.width_; ++j) {
            Color col;
            col.b_ = std::min(1.0f, std::max(0.0f, (-1) * (vec[i][j + 1].b_ + vec[i + 1][j].b_ + vec[i + 1][j + 2].b_ +
                                                           vec[i + 2][j + 1].b_) +
                                                       vec[i + 1][j + 1].b_ * (a)));
            col.r_ = std::min(1.0f, std::max(0.0f, (-1) * (vec[i][j + 1].r_ + vec[i + 1][j].r_ + vec[i + 1][j + 2].r_ +
                                                           vec[i + 2][j + 1].r_) +
                                                       vec[i + 1][j + 1].r_ * (a)));
            col.g_ = std::min(1.0f, std::max(0.0f, (-1) * (vec[i][j + 1].g_ + vec[i + 1][j].g_ + vec[i + 1][j + 2].g_ +
                                                           vec[i + 2][j + 1].g_) +
                                                       vec[i + 1][j + 1].g_ * (a)));
            new_im.SetColor(col, static_cast<int>(j), static_cast<int>(i));
        }
    }
    copy = new_im;
}

void FilterSharpening::UseFilter(Image& image, std::vector<std::string> vec) {
    FilterSR(image);
}
