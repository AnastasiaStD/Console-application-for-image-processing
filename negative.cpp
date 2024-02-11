#include "negative.h"

void FilterN(Image& copy) {
    for (size_t i = 0; i < copy.height_; ++i) {
        for (size_t j = 0; j < copy.width_; ++j) {
            copy.pixels_[i][j].b_ = (1 - copy.pixels_[i][j].b_);
            copy.pixels_[i][j].g_ = (1 - copy.pixels_[i][j].g_);
            copy.pixels_[i][j].r_ = (1 - copy.pixels_[i][j].r_);
        }
    }
}

void FilterNegative::UseFilter(Image& image, std::vector<std::string> vec) {
    FilterN(image);
}