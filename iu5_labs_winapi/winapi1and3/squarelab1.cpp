#include "squarelab1.h"

SquareLab1::SquareLab1() {
    small->red = 0.2;
    small->green = 0.2;
    small->blue = 0.2;

    medium->red = 0.5;
    medium->green = 0.5;
    medium->blue = 0.5;

    kingSize->red = 0.8;
    kingSize->green = 0.8;
    kingSize->blue = 0.8;
}

void SquareLab1::swapColors(Square* first, Square* second) {
    Square buff;
    buff = *first;
    *first = *second;
    *second = buff;
}

void SquareLab1::setRed(double intensivity, Square* size) {
    size->red = intensivity;
}

void SquareLab1::setGreen(double intensivity, Square* size) {
    size->green = intensivity;
}

void SquareLab1::setBlue(double intensivity, Square* size) {
    size->blue = intensivity;
}

