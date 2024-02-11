#include "my_filter_2.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <tuple>

float CalcM(std::vector<float> v) {
    size_t size = v.size();
    if (size == 0) {
        return 0;
    } else {
        sort(v.begin(), v.end());
        if (size % 2 == 0) {
            return (v[size / 2 - 1] + v[size / 2]) / 2;
        } else {
            return v[size / 2];
        }
    }
}

void FilterMy2(Image& image) {
    int new_h = image.height_ + 2;
    int new_w = image.width_ + 2;
    std::vector<std::vector<Color>> vec(new_h);
    for (size_t i = 0; i < new_h; ++i) {
        vec[i].resize(new_w);
        for (size_t j = 0; j < new_w; ++j) {
            if (i != 0 && j != 0 && j != (new_w - 1) && i != (new_h - 1)) {
                vec[i][j] = image.pixels_[i - 1][j - 1];
            } else if (i == 0 && j != 0 && j != new_w - 1) {
                vec[i][j] = image.pixels_[i][j - 1];
            } else if (j == 0 && i != 0 && i != new_h - 1) {
                vec[i][j] = image.pixels_[i - 1][j];
            } else if (i == (new_h - 1) && j != 0 && j != (new_w - 1)) {
                vec[i][j] = image.pixels_[i - 2][j - 1];
            } else if (j == (new_w - 1) && i != (new_h - 1) && i != 0) {
                vec[i][j] = image.pixels_[i - 1][j - 2];
            }
        }
    }
    Image new_im = Image(image.width_, image.height_);

    for (size_t i = 0; i < image.height_; ++i) {
        for (size_t j = 0; j < image.width_; ++j) {
            std::vector<float> vec_r = {vec[i][j].r_,     vec[i][j + 1].r_,     vec[i][j + 2].r_,
                                        vec[i + 1][j].r_, vec[i + 1][j + 1].r_, vec[i + 1][j + 2].r_,
                                        vec[i + 2][j].r_, vec[i + 2][j + 1].r_, vec[i + 2][j + 2].r_};
            std::vector<float> vec_b = {vec[i][j].b_,     vec[i][j + 1].b_,     vec[i][j + 2].b_,
                                        vec[i + 1][j].b_, vec[i + 1][j + 1].b_, vec[i + 1][j + 2].b_,
                                        vec[i + 2][j].b_, vec[i + 2][j + 1].b_, vec[i + 2][j + 2].b_};
            std::vector<float> vec_g = {vec[i][j].g_,     vec[i][j + 1].g_,     vec[i][j + 2].g_,
                                        vec[i + 1][j].g_, vec[i + 1][j + 1].g_, vec[i + 1][j + 2].g_,
                                        vec[i + 2][j].g_, vec[i + 2][j + 1].g_, vec[i + 2][j + 2].g_};

            float m_r = CalcM(vec_r);
            float m_b = CalcM(vec_b);
            float m_g = CalcM(vec_g);

            Color col = {m_r, m_b, m_g};

            new_im.SetColor(col, static_cast<int>(j), static_cast<int>(i));
        }
    }

    image = new_im;
}

void FilterMyFilter2::UseFilter(Image& image, std::vector<std::string> vec) {
    FilterMy2(image);
}
