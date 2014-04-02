#include <QDebug>
#include "triangle.h"
#include "edge.h"

const double Triangle::RAD_IN_GRAD = M_PI / 180.0;
const double Triangle::MIN_SCALE_X = 0.0;
const double Triangle::MAX_SCALE_X = 10.0;
const double Triangle::MIN_SCALE_Y = 0.0;
const double Triangle::MAX_SCALE_Y = 10.0;
const double Triangle::MAX_ANGLE = 360.0;

const double Triangle::DEFAULT_SCALE_X = 1.0;
const double Triangle::DEFAULT_SCALE_Y = 1.0;

Triangle::Triangle(const TexturedPoint& a, const TexturedPoint& b, const TexturedPoint& c)
{
    points.push_back(a);
    points.push_back(b);
    points.push_back(c);

    texture = 0;
    currAngle = 0;
    currScaleX = DEFAULT_SCALE_X;
    currScaleY = DEFAULT_SCALE_Y;
}

void Triangle::formRotMatX(float *m, float angle) {
    m[0] = cos(RAD_IN_GRAD*angle);
    m[1] = sin(RAD_IN_GRAD*angle);
}

void Triangle::formRotMatY(float *m, float angle) {
    m[0] = -sin(RAD_IN_GRAD*angle);
    m[1] = cos(RAD_IN_GRAD*angle);
}

void Triangle::rotate(float angle) {
    float rotMatX[2];
    float rotMatY[2];
    float xc = (points[0].x() + points[1].x() + points[2].x())/ 3.0;
    float yc = (points[0].y() + points[1].y() + points[2].y())/ 3.0;

    formRotMatX(rotMatX, angle);
    formRotMatY(rotMatY, angle);
    for (int i = 0; i < (int)points.size(); ++i) {
        int oldX = points[i].x();
        int oldY = points[i].y();
        int newX = round( (oldX-xc) * rotMatX[0] + (oldY-yc) * rotMatX[1] + xc);
        int newY = round( (oldX-xc) * rotMatY[0] + (oldY-yc) * rotMatY[1] + yc);
        qDebug() << newX << newY;
        points[i].setX(newX);
        points[i].setY(newY);
    }
}

void Triangle::setTexture(Texture* texture) {
    this->texture = texture;
}

void Triangle::draw(Canvas& canvas) {
    std::sort(points.begin(), points.end());

    Edge ab(points.at(0), points.at(1));
    Edge ac(points.at(0), points.at(2));
    Edge bc(points.at(1), points.at(2));


    std::vector<Edge> edges;
    edges.push_back(ab);
    edges.push_back(ac);

    int curY = points.at(0).y();
    int nextY = points.at(1).y();

    while (curY <= points.at(2).y()) {

        while (curY <= nextY)
        {
            std::vector<TexturedPoint> borderX;

            for (int i = 0; i < (int)edges.size(); ++i) {
                int n = curY - edges[i].getA().y() ;
                double curX = (edges[i].getA().x()) + n*edges[i].getK();
                TexturedPoint texCoord(curX, curY);
                texCoord.calcTextureCoordinates(edges[i].getA(), edges[i].getB());
                borderX.push_back(texCoord);

            }
            std::sort(borderX.begin(), borderX.end(), TexturedPoint::compX);

            for (int x = borderX.front().x(); x < borderX.back().x(); ++x) {
                TexturedPoint curPoint(x, curY);
                curPoint.calcTextureCoordinates(borderX.front(),borderX.back());
                canvas.drawPixel(x, curY, TexturedPoint::transformToColor(curPoint.getTexX(), curPoint.getTexY()));
            }
            ++curY;
        }
        edges.erase(edges.begin());
        edges.push_back(bc);

        ++curY;
        nextY = points.at(2).y();
    }

}
