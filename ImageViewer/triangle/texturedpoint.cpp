#include <QDebug>
#include "texturedpoint.h"
#include <cmath>

TexturedPoint::TexturedPoint(double X, double Y):QPointF(X,Y)
{
    texX = INVALID;
    texY = INVALID;
}

TexturedPoint::TexturedPoint(double X, double Y, double texX, double texY)
    : QPointF(X, Y), texX(texX), texY(texY)
{

}


double TexturedPoint::getTexY() const
{
    return texY;
}

void TexturedPoint::setTexY(double value)
{
    texY = value;
}

double TexturedPoint::getTexX() const
{
    return texX;
}

void TexturedPoint::setTexX(double value)
{
    texX = value;
}

bool TexturedPoint::compX(const TexturedPoint &a, const TexturedPoint &b){
    return a.x() < b.x();
}

QColor TexturedPoint::transformToColor(double xt, double yt) {
    int r = floor(xt == 1.0 ? 255 : fabs(xt) * 256.0);
    int g = floor(yt == 1.0 ? 255 : fabs(yt) * 256.0);
    if (r > 255 || r < 0  || g > 255 || g < 0 )
    qDebug() << r << g << xt << yt;

   return QColor(r, g, 0);
}

void TexturedPoint::calcTextureCoordinates(const TexturedPoint& a, const TexturedPoint& b){
    double k = 0;
// TODO : scalar = sqrt(norm)
    if (b.x() != a.x()) {
        k = fabs((this->x() - a.x()) * 1.0 / (b.x() - a.x()));
    }
    if (a.y() != b.y() ) {
        k = fabs((this->y() - a.y()) * 1.0/ (b.y() - a.y()));
    }

    if (k < 0 || k > 1){
        qDebug() << k ;
    }
    texX = a.getTexX() + (b.getTexX() - a.getTexX())* k;
    texY = a.getTexY() + (b.getTexY() - a.getTexY())* k;

}
