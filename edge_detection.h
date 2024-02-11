#pragma once

#include "filters.h"
#include "grayscale.h"

Image FilterED(const Image& image, unsigned char threshold);

class FilterEdgeDetection : public Filter {
public:
    void UseFilter(Image& image, std::vector<std::string> vec) override;
    ~FilterEdgeDetection() override = default;
};
