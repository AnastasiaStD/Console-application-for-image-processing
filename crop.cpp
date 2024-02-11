#include "crop.h"
#include <algorithm>
#include <iostream>
#include <string>

Image FilterCr(Image& image, int right, int down) {
    int new_x = std::min(right, image.width_);
    int new_y = std::min(down, image.height_);
    Image image2 = Image(new_x, new_y);
    for (size_t x = image.height_ - new_y; x < image.height_; ++x) {
        for (size_t y = 0; y < new_x; ++y) {
            image2.pixels_[x - image.height_ + new_y][y] = image.pixels_[x][y];
        }
    }
    image = image2;
    return image;
}

void FilterCrop::UseFilter(Image& image, std::vector<std::string> vec) {
    int w = std::stoi(vec[0]);
    int h = std::stoi(vec[1]);
    FilterCr(image, w, h);
}
/*
Image FilterCr(const Image& image, int right, int down) {
   int new_x = std::min(right, image.width_());
   int new_y = std::min(down, image.height_());
   Image image2 = Image(new_x, new_y);
   for (size_t y = 0; y < new_y; ++y) {
       for (size_t x = 0; x < new_x; ++x) {
           image2.SetColor(image.GetColor(static_cast<int>(x), static_cast<int>(y)), static_cast<int>(x),
                           static_cast<int>(y));
       }
   }
   return image2;
}

void FilterCrop::UseFilter(Image& image, std::vector<std::string>& vec) {
   int w = std::stoi(vec[0]);
   int h = std::stoi(vec[1]);
   image = FilterCr(image, w, h);
}
*/