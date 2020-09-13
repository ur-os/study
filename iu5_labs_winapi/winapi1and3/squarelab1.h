#ifndef SQUARELAB1_H
#define SQUARELAB1_H

#include "QGLWidget"

class SquareLab1 {

public:
    struct Square{
        double red = 0;
        double green = 0;
        double blue = 0;
    };

    Square* small = new Square;
    Square* medium = new Square;
    Square* kingSize = new Square;

    void setRed(double intensivity, Square* size);
    void setGreen(double intensivity, Square* size);
    void setBlue(double intensivity, Square* size);
    void swapColors(Square* first, Square* second);

    SquareLab1();
};

#endif // SQUARELAB1_H
