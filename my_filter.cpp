#include "my_filter.h"

void FilterMine(Image& copy) {
    // float a = 4;  // DISABLE _NOLINT
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
    float e = 5.0f;  // DISABLE _NOLINT
    for (size_t i = 0; i < copy.height_; ++i) {
        for (size_t j = 0; j < copy.width_; ++j) {
            Color col;
            float b =
                std::max(0.0f, (-1 * e) * vec[i][j].b_ + (-1 * e) * vec[i][j + 1].b_ + (-1 * e) * vec[i + 1][j].b_ +
                                   e * vec[i + 1][j + 2].b_ + e * vec[i + 2][j + 2].b_ + e * vec[i + 2][j + 1].b_);
            float r =
                std::max(0.0f, (-1 * e) * vec[i][j].r_ + (-1 * e) * vec[i][j + 1].r_ + (-1 * e) * vec[i + 1][j].r_ +
                                   e * vec[i + 1][j + 2].r_ + e * vec[i + 2][j + 2].r_ + e * vec[i + 2][j + 1].r_);
            float g =
                std::max(0.0f, (-1 * e) * vec[i][j].g_ + (-1 * e) * vec[i][j + 1].g_ + (-1 * e) * vec[i + 1][j].g_ +
                                   e * vec[i + 1][j + 2].g_ + e * vec[i + 2][j + 2].g_ + e * vec[i + 2][j + 1].g_);
            col.b_ = std::min(1.0f, b);
            col.r_ = std::min(1.0f, r);
            col.g_ = std::min(1.0f, g);
            new_im.SetColor(col, static_cast<int>(j), static_cast<int>(i));
        }
    }
    copy = new_im;
}

void FilterMyFilter::UseFilter(Image& image, std::vector<std::string>) {
    FilterMine(image);
}
