#pragma once

#include "filters.h"

void FilterMy2(Image& image);

class FilterMyFilter2 : public Filter {
public:
    void UseFilter(Image& image, std::vector<std::string> vec) override;
    ~FilterMyFilter2() override = default;
};
