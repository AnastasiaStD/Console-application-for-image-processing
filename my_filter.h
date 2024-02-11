#pragma once

#include "filters.h"

void FilterMy(const Image& image);

class FilterMyFilter : public Filter {
public:
    // FilterMyFilter();
    void UseFilter(Image& image, std::vector<std::string> vec) override;
    ~FilterMyFilter() override = default;
};
