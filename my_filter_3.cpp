#include "my_filter_3.h"
#include <algorithm>
#include <cmath>
#include <vector>

const float CONSTANT_PI = static_cast<float>(M_PI);
const int GAUSSIAN_HALF_WIDTH = 3;  // DISABLE _NOLINT
const float EPSILON = 1e-6;         // DISABLE _NOLINT

void FilterMy3(Image& image, float s) {
    const float sigma = s + EPSILON;
    std::vector<float> kernel;
    kernel.reserve(2 * GAUSSIAN_HALF_WIDTH + 1);  // DISABLE _NOLINT
    for (int i = -GAUSSIAN_HALF_WIDTH; i <= GAUSSIAN_HALF_WIDTH; ++i) {
        const float val = std::exp(-0.5f * static_cast<float>(i * i) / (sigma * sigma)) /
                          (sigma * std::sqrt(2 * CONSTANT_PI));  // DISABLE _NOLINT
        kernel.emplace_back(val);
    }
    float sum = NAN;
    const int width = image.width_;
    const int height = image.height_;
    const auto copy = image;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            sum = 0.0f;
            for (int k = -GAUSSIAN_HALF_WIDTH; k <= GAUSSIAN_HALF_WIDTH; ++k) {
                const int coord = std::min(std::max(j + k, 0), width - 1);
                sum += kernel[k + GAUSSIAN_HALF_WIDTH] * copy.pixels_[i][coord].r_;
            }
            image.pixels_[i][j].r_ = sum;
        }
    }
    for (int j = 0; j < width; ++j) {
        for (int i = 0; i < height; ++i) {
            sum = 0.0f;  // DISABLE _NOLINT
            for (int k = -GAUSSIAN_HALF_WIDTH; k <= GAUSSIAN_HALF_WIDTH; ++k) {
                const int coord = std::min(std::max(i + k, 0), height - 1);
                sum += kernel[k + GAUSSIAN_HALF_WIDTH] * image.pixels_[coord][j].r_;
            }
            image.pixels_[i][j].r_ = sum;
        }
    }
}

void FilterMyFilter3::UseFilter(Image& image, std::vector<std::string> vec) {
    float s = std::stof(vec[0]);
    FilterMy3(image, s);
}
