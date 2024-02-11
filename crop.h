#pragma once
#include "filters.h"

Image FilterCr(Image& image, int right, int down);

class FilterCrop : public Filter {
public:
    // FilterCrop();
    void UseFilter(Image& image, std::vector<std::string>) override;
    ~FilterCrop() override = default;
};
