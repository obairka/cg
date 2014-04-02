#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <cmath>
#include "canvas.h"
#include "texturedpoint.h"
#include "texture.h"

class Triangle
{
private:
    Texture* texture;
    std::vector<TexturedPoint> points;
    float currAngle;
    float currScaleX;
    float currScaleY;

public:
    Triangle(const TexturedPoint& a, const TexturedPoint& b, const TexturedPoint& c);
    void setTexture(Texture* texture);
    void draw(Canvas& canvas);
    void rotate(float angle);

    void scaleX(float q);
    void scaleY(float q);

/*
 *  Вспомогательные методы
 */
private:
    void formRotMatX(float* m, float angle);
    void formRotMatY(float* m, float angle);

/*
 *  Статические параметры
 */
public:
    static const double RAD_IN_GRAD;
    static const double MIN_SCALE_X;
    static const double MAX_SCALE_X;
    static const double MIN_SCALE_Y;
    static const double MAX_SCALE_Y;
    static const double MAX_ANGLE;

    static const double DEFAULT_SCALE_X;
    static const double DEFAULT_SCALE_Y;

};

#endif // TRIANGLE_H
