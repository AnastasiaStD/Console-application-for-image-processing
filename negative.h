#pragma once

#include "filters.h"

void FilterN(const Image& image);

class FilterNegative : public Filter {
public:
    // FilterNegative();
    void UseFilter(Image& image, std::vector<std::string> vec) override;
    ~FilterNegative() override = default;
};
