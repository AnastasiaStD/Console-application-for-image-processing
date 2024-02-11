
#include <stdexcept>
#include "image.h"
#include <string>
#include "helper.h"

#include "crop.h"
#include "edge_detection.h"
#include "negative.h"
#include "grayscale.h"
#include "my_filter.h"
#include "sharpening.h"
#include "blur.h"
#include "my_filter_2.h"
#include "my_filter_3.h"

int main(int argc, char** argv) {
    if (argc == 2) {
        throw std::runtime_error("Did not put out-directory");
    }
    if (argc == 1) {
        General();
        return 1;
    }
    Image copy(0, 0);
    copy.Read(argv[1]);
    for (int i = 3; i < argc; ++i) {
        std::string argument = argv[i];
        std::vector<std::string> arg;
        if (argument == "-gs") {
            FilterGrayscale filter_grayscale_ptr;
            filter_grayscale_ptr.UseFilter(copy, arg);
        } else if (argument == "-neg") {
            FilterNegative filter_neg_ptr;
            filter_neg_ptr.UseFilter(copy, arg);
        } else if (argument == "-crop") {
            if (i > argc - 3) {
                throw std::runtime_error("Reading command line parameters was failed");
            }
            FilterCrop filter_crop_ptr;
            try {
                std::stoi(argv[i + 1]);
                std::stoi(argv[i + 2]);
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Invalid command line argument");
            }
            arg.push_back(argv[i + 1]);
            arg.push_back(argv[i + 2]);
            filter_crop_ptr.UseFilter(copy, arg);
        } else if (argument == "-sharp") {
            FilterSharpening filter_sharp_ptr;
            filter_sharp_ptr.UseFilter(copy, arg);
            // copy.FilterSR(copy);
        } else if (argument == "-edge") {
            FilterEdgeDetection filter_edge_ptr;
            arg.push_back(argv[i + 1]);
            filter_edge_ptr.UseFilter(copy, arg);
        } else if (argument == "-mine") {
            FilterMyFilter filter_my_ptr;
            filter_my_ptr.UseFilter(copy, arg);
        } else if (argument == "-blur") {
            if (i > argc - 2) {
                throw std::runtime_error("Reading command line parameters was failed");
            }
            try {
                std::stof(argv[i + 1]);
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Invalid command line argument");
            }
            FilterBlur filter_blur_ptr;
            arg.push_back(argv[i + 1]);
            filter_blur_ptr.UseFilter(copy, arg);
        } else if (argument == "-mine2") {
            FilterMyFilter2 filter_my_ptr2;
            filter_my_ptr2.UseFilter(copy, arg);
        } else if (argument == "-mine3") {
            if (i > argc - 2) {
                throw std::runtime_error("Reading command line parameters was failed");
            }
            try {
                std::stof(argv[i + 1]);
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Invalid command line argument");
            }
            FilterMyFilter3 filter_blur_ptr;
            arg.push_back(argv[i + 1]);
            filter_blur_ptr.UseFilter(copy, arg);
        }
    }
    copy.Export(argv[2]);
}