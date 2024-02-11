#include "blur.h"
#include <string>
#include <cmath>
#include <algorithm>

void FilterBl(Image& copy, float sigma) {
    float sig = std::abs(sigma);
    auto copy1 = copy;
    int start = static_cast<int>((-1) * std::ceil(sig * 3));  // DISABLE _NOLINT
    int end = static_cast<int>(std::ceil(sig * 3));           // DISABLE _NOLINT
    std::vector<float> vec_stolb(end - start + 1);
    float coef = std::pow(1.0f / (2 * M_PI * sig * sig), 0.5);  // DISABLE _NOLINT
    for (int i = start; i <= end; ++i) {
        vec_stolb[i - start] = exp(-i * i / (2 * sig * sig));  // DISABLE _NOLINT
    }
    for (size_t x = 0; x < copy.height_; ++x) {
        for (size_t y = 0; y < copy.width_; ++y) {
            Color col;
            for (int i = start; i <= end; ++i) {
                int norma = std::min(static_cast<int>(copy.height_ - 1), std::max(0, static_cast<int>(x) + i));
                col.r_ += vec_stolb[i - start] * copy.pixels_[norma][y].r_ * coef;
                col.g_ += vec_stolb[i - start] * copy.pixels_[norma][y].g_ * coef;
                col.b_ += vec_stolb[i - start] * copy.pixels_[norma][y].b_ * coef;
            }
            copy1.SetColor(col, static_cast<int>(y), static_cast<int>(x));
        }
    }
    for (size_t x = 0; x < copy.height_; ++x) {
        for (size_t y = 0; y < copy.width_; ++y) {
            Color col;
            for (int i = start; i <= end; ++i) {
                int norma = std::min(static_cast<int>(copy.width_ - 1), std::max(0, static_cast<int>(y) + i));
                col.r_ += vec_stolb[i - start] * copy1.pixels_[x][norma].r_ * coef;
                col.g_ += vec_stolb[i - start] * copy1.pixels_[x][norma].g_ * coef;
                col.b_ += vec_stolb[i - start] * copy1.pixels_[x][norma].b_ * coef;
            }
            copy.SetColor(col, static_cast<int>(y), static_cast<int>(x));
        }
    }
}

void FilterBlur::UseFilter(Image& image, std::vector<std::string> vec) {
    float s = std::stof(vec[0]);
    FilterBl(image, s);
}
