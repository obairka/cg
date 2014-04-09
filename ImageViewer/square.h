#ifndef SQUARE_H
#define SQUARE_H

#include "triangle/triangle.h"
#include "canvas.h"


class Square : public QObject
{
    Q_OBJECT
private:
    double xc;
    double yc;
    double leftX, rightX;
    double downY, upY;
    Triangle leftDownTriangle;
    Triangle rightUpTriangle;
    int size;
    int maxX;
    int maxY;
public:
    // Задается стороной и центром
    Square(int size, double xc, double yc);
    void draw(Canvas& canvas);
    void setMax(int maxX, int maxY);

signals:
    void angleChanged();
    void scaleChanged();
    void centerChanged();
public slots:

    void setCenter(double xc, double yc);
    void setSize(int size);
    void rotate(double agle);
    void scaleX(double scaleX);
    void scaleY(double scaleY);

};

#endif // SQUARE_H
