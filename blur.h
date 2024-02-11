#pragma once

#include "filters.h"
void FilterBl(Image& image, float sigma);

class FilterBlur : public Filter {
public:
    // FilterBlur();
    void UseFilter(Image& image, std::vector<std::string>) override;
    ~FilterBlur() override = default;
};
