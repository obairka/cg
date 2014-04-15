#ifndef TEXTUREDPOINT_H
#define TEXTUREDPOINT_H

#include <QPointF>
#include <cmath>
#include <QColor>

class TexturedPoint : public QPointF
{
private:
    double texX;
    double texY;
public:
    TexturedPoint(double X,  double Y, double texX, double texY);
    TexturedPoint(double X,  double Y);

    void calcTextureCoordinates(const TexturedPoint& a, const TexturedPoint& b);

    double getTexX() const;
    double getTexY() const;
    void setTexX(double value);
    void setTexY(double value);

    friend bool operator<(const TexturedPoint& a, const TexturedPoint& b)  {
        return a.y() < b.y();
    }
    static QColor transformToColor(double tx, double ty);
    static bool compX(const TexturedPoint& a, const TexturedPoint& b);
private:
    static double norm(double x, double y) {
        return sqrt(pow(x, 2)+pow(y,2));
    }

    static const double INVALID = -1;
};

#endif // TEXTUREDPOINT_H
