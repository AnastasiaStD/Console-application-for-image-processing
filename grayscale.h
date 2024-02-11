#pragma once

#include "filters.h"

Image FilterGS(const Image& image);

class FilterGrayscale : public Filter {
public:
    // FilterGrayscale();
    void UseFilter(Image& image, std::vector<std::string> vec) override;
    ~FilterGrayscale() override = default;
};
