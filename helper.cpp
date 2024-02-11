#include "helper.h"
#include <iostream>

void General() {
    std::cout << "Filters in image processor : " << std::endl;
    std::cout << "1. -ng : преобразует изображение в негатив " << std::endl;
    std::cout << "2. -crop width height : обрезает изображение до заданных ширины и высоты. Используется верхняя левая "
                 "часть изображения. "
              << std::endl;

    std::cout << "3. -gs : преобразует изображение в оттенки серого " << std::endl;
    std::cout << "4. -sharp : фильтр-повышение резкости " << std::endl;
    std::cout << "5. -edge threshold : выделение границ " << std::endl;
    std::cout << "6. -blur sigma :  эффект размытия " << std::endl;
    std::cout << "7. -mine :  собственный фильтр, скучный рельеф изображения " << std::endl;
    std::cout << "8. -mine2 :  собстввенный фильтр, медианный фильтр  " << std::endl;
    std::cout << "9. -mine2 :  собстввенный фильтр, синева " << std::endl;
}

void Error() {
    std::cout << "Need more arguments" << std::endl;
}
