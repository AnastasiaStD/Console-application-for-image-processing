#pragma once

#include <vector>

struct Color {
    float r_, g_, b_;

    Color();

    Color(float г, float g, float b);

    Color(const Color &other);

    ~Color();

    Color operator=(Color col);

    bool operator==(Color col) const;
};

class Image {
public:
    Image(int width, int height, std::vector<std::vector<Color>> colors);
    Image(int width, int height);
    Image();
    ~Image();

    Color GetColor(int x, int y) const;

    void SetColor(const Color &color, int x, int y);

    int GetWidth() const;

    int GetHeight() const;

    Image operator=(const Image &other);
    bool operator==(const Image &other) const;

    void Read(const char *path);

    void Export(const char *path) const;

public:
    int width_;
    int height_;
    std::vector<std::vector<Color>> pixels_;
};
