#pragma once

#include "filters.h"

void FilterSR(const Image& image);

class FilterSharpening : public Filter {
public:
    // FilterSharpening();
    void UseFilter(Image& image, std::vector<std::string> vec) override;
    ~FilterSharpening() override = default;
};
