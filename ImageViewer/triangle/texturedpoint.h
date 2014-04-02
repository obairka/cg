#ifndef TEXTUREDPOINT_H
#define TEXTUREDPOINT_H

#include <QPoint>
#include <QColor>

class TexturedPoint : public QPoint
{
private:
    double texX;
    double texY;
public:
    TexturedPoint(int X,  int Y, double texX, double texY);
    TexturedPoint(int X,  int Y);

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
    static const double INVALID = -1;
};

#endif // TEXTUREDPOINT_H
