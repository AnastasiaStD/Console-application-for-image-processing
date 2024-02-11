#pragma once
#include "image.h"
#include "string"

class Filter {
public:
    virtual void UseFilter(Image& image, std::vector<std::string>) = 0;
    virtual ~Filter() = default;
};
