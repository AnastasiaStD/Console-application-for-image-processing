#pragma once

#include "filters.h"

void FilterMy3(Image& image, float s);

class FilterMyFilter3 : public Filter {
public:
    void UseFilter(Image& image, std::vector<std::string> vec) override;
    ~FilterMyFilter3() override = default;
};
