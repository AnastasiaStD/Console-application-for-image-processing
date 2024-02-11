#include "grayscale.h"

void FilterGS(Image& copy) {
    for (size_t i = 0; i < copy.height_; ++i) {
        for (size_t j = 0; j < copy.width_; ++j) {
            float color = copy.pixels_[i][j].r_ * 299 / 1000 + copy.pixels_[i][j].g_ * 587 / 1000 +  // DISABLE_NOLINT
                          copy.pixels_[i][j].b_ * 114 / 1000;                                        // DISABLE_NOLINT
            copy.pixels_[i][j].b_ = color;
            copy.pixels_[i][j].g_ = color;
            copy.pixels_[i][j].r_ = color;
        }
    }
}

void FilterGrayscale::UseFilter(Image& image, std::vector<std::string> vec) {
    FilterGS(image);
}
