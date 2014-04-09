#include "triangle/texturedpoint.h"
#include "square.h"
#include <QDebug>

Square::Square(int size, double xc, double yc)
    :
        // leftX = xc - size*1.0/2  leftY =yc - size*1.0/2
        // rightX = xc + size*1.0/2 rightY = yc + size*1.0/2
      leftX(xc-size*1.0/2), rightX(xc+size*1.0/2),
      downY(yc-size*1.0/2), upY(yc+size*1.0/2),
      leftDownTriangle(TexturedPoint(leftX, downY, 0, 0), TexturedPoint(leftX, upY, 0, 1),
                      TexturedPoint(rightX, upY, 1, 1)),
      rightUpTriangle(TexturedPoint(leftX, downY, 0, 0), TexturedPoint(rightX, downY, 1, 0),
                      TexturedPoint(rightX, upY, 1, 1))


{
    setCenter(xc,yc);
    setSize(size);
    setMax(rightX, upY);
}

void Square::draw(Canvas &canvas){
    rightUpTriangle.draw(canvas);
    leftDownTriangle.draw(canvas);
}

void Square::setCenter(double xc, double yc){
    this->xc = xc;
    this->yc = yc;
    leftDownTriangle.setRotateCenter(xc, yc);
    rightUpTriangle.setRotateCenter(xc, yc);
}

void Square::setMax(int maxX, int maxY){
    rightUpTriangle.setMaxX(maxX);
    rightUpTriangle.setMaxY(maxY);
    leftDownTriangle.setMaxX(maxX);
    leftDownTriangle.setMaxY(maxY);
}

void Square::setSize(int size) {
    this->size = size;
    leftX = xc-size*1.0/2;
    rightX = xc+size*1.0/2;
    downY = yc-size*1.0/2;
    upY = yc+size*1.0/2;
}

void Square::rotate(double angle) {
    leftDownTriangle.rotate(angle);
    rightUpTriangle.rotate(angle);
    emit angleChanged();
}

void Square::scaleX(double scaleX) {
    leftDownTriangle.scaleX(scaleX);
    rightUpTriangle.scaleX(scaleX);
    emit scaleChanged();
}

void Square::scaleY(double scaleY) {
    leftDownTriangle.scaleY(scaleY);
    rightUpTriangle.scaleY(scaleY);
    emit scaleChanged();
}
