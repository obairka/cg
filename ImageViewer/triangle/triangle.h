#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include <vector>
#include <cmath>
#include "canvas.h"
#include "texturedpoint.h"
#include "texture.h"

class Triangle : public QObject
{
    Q_OBJECT
private:
    Texture* texture;                   // get point color
    std::vector<TexturedPoint> points;
    double rotCenterX;
    double rotCenterY;

    double currAngle;
    double currScaleX;
    double currScaleY;

    int maxY; // для клипирования
    int maxX; // для клипирования

public:
    Triangle(const TexturedPoint& a, const TexturedPoint& b, const TexturedPoint& c);
    void setTexture(Texture* texture);
    void draw(Canvas& canvas);
/*
 * клипирование
 */
    void setMaxX(int maxX);
    void setMaxY(int maxY);
signals:
    void angleChanged();
    void scaleChanged();
    void centerChanged();
public slots:
    void rotate(double angle);

    void setRotateCenter(double xc, double xy);
    void scaleX(double q);
    void scaleY(double q);

private:

    void transform(std::vector<TexturedPoint>& new_points);


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
