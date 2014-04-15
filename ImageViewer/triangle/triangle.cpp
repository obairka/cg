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

    rotCenterX = (a.x() + b.x() + c.x())/3.;
    rotCenterY = (a.y() + b.y() + c.y())/3.;
    maxX = c.x();
    maxY = c.y();
}

void Triangle::setRotateCenter(double xc, double yc){
    rotCenterX = xc;
    rotCenterY = yc;
    emit centerChanged();
}

void Triangle::scaleX(double q){
    currScaleX = q;
    emit scaleChanged();
}

void Triangle::scaleY(double q){
    currScaleY = q;
    emit scaleChanged();
}


void Triangle::setMaxX(int maxX){
    this->maxX = maxX;
}

void Triangle::setMaxY(int maxY){
    this->maxY = maxY;
}

void Triangle::formRotMat(double rotMat[2][2]) {
    double angle = currAngle;
    rotMat[0][0] = cos(RAD_IN_GRAD*angle);
    rotMat[0][1] = sin(RAD_IN_GRAD*angle);
    rotMat[1][0] = -rotMat[0][1];
    rotMat[1][1] = rotMat[0][0];
}

void Triangle::rotate(double angle) {
    currAngle = angle;
    emit angleChanged();
}

void Triangle::setTexture(Texture* texture) {
    this->texture = texture;
}

void Triangle::applyRotation(std::vector<TexturedPoint>& new_points, const std::vector<TexturedPoint>& old_points){
    double rotMat[2][2];
    formRotMat(rotMat);
    for (int i = 0; i < (int)old_points.size(); ++i) {
        double oldX = old_points[i].x();
        double oldY = old_points[i].y();

        double newX = (oldX-rotCenterX) * rotMat[0][0] + (oldY-rotCenterY) * rotMat[0][1] + rotCenterX;
        double newY =  (oldX-rotCenterX) * rotMat[1][0] + (oldY-rotCenterY) * rotMat[1][1] + rotCenterY;
        TexturedPoint new_point = old_points[i];
        qDebug() << oldX << oldY << "->" << newX << newY;
        new_point.setX(newX);
        new_point.setY(newY);
        new_points.push_back(new_point);
    }
}

void Triangle::formScaleMat(double rotScale[2][2]){
    rotScale[0][0] = currScaleX;
    rotScale[0][1] = 0;
    rotScale[1][0] = 0;
    rotScale[1][1] = currScaleY;
}

void Triangle::applyScaling(std::vector<TexturedPoint> &new_points){
    double scaleMat[2][2];
    formScaleMat(scaleMat);
    for (int i = 0; i < (int)new_points.size(); ++i) {
        double oldX = new_points[i].x();
        double oldY = new_points[i].y();
        double newX = (oldX-rotCenterX) * scaleMat[0][0] +  (oldY-rotCenterY) * scaleMat[0][1]  +rotCenterX;
        double newY = (oldX-rotCenterX)  * scaleMat[1][0] + (oldY-rotCenterY)  * scaleMat[1][1] +rotCenterY;


        new_points[i].setX(newX);
        new_points[i].setY(newY);

    }
}


void Triangle::draw(Canvas& canvas) {

    std::vector<TexturedPoint> points;
    applyRotation(points, this->points);
    applyScaling(points);
     for (int i = 0; i < (int)points.size(); ++i) {
         qDebug() << points[i].x() << points[i].y();
     }
    std::sort(points.begin(), points.end());

    std::vector<Edge> edges;

    int minY = (points.front().y() < 0) ? 0: points.front().y();
    int maxY = (points.back().y() < this->maxY) ? points.back().y() : this->maxY;

    int curY = minY;
    int i = 0;

    while (curY <= maxY){

        int nextY = maxY;

        while ( i != (int)points.size() && trunc(points[i].y()) <= curY){
            TexturedPoint a = points[i];
            TexturedPoint b = points[(points.size() - i-1) % points.size()];
            TexturedPoint c = points[(i+1) % points.size()];

            if (b.y() > curY ) {
                edges.push_back(Edge(a,b));
                if ( b.y() < nextY ) {
                    nextY = b.y() ;
                }
            }
            if (c.y() > curY) {
                edges.push_back(Edge(a,c));
                if ( c.y() < nextY) {
                    nextY = c.y();
                }
            }
            ++i;
        }

        if (edges.empty()) {
           if(i != (int)points.size()) {
               curY = points[i].y();

               nextY = maxY;
               continue;
           }
           break;
        }
        if (i != (int)points.size() && nextY > points[i].y()) {
            nextY = points[i].y();
        }

        while(curY <= nextY && curY <= maxY) {

            std::vector<TexturedPoint> borderX;
            for (int i = 0; i < (int)edges.size(); ++i) {
                int n = curY - edges[i].getA().y() ;
                double curX = (edges[i].getA().x()) + n*edges[i].getK();
                TexturedPoint texCoord(curX, curY);
                texCoord.calcTextureCoordinates(edges[i].getA(), edges[i].getB());
                borderX.push_back(texCoord);
            }

            std::sort(borderX.begin(), borderX.end(), TexturedPoint::compX);
            int begin = borderX.front().x() >0 ? borderX.front().x() : 0;

            for (int x = begin; x < borderX.back().x() && x < maxX; ++x) {

                TexturedPoint curPoint(x, curY);
                curPoint.calcTextureCoordinates(borderX.front(),borderX.back());

                canvas.drawPixel(x, curY, TexturedPoint::transformToColor(curPoint.getTexX(), curPoint.getTexY()));
            }

            ++curY;
        }
        //if (curY >= maxY) break;
        std::vector<Edge>::iterator iter = edges.begin();
        for(; iter != edges.end(); ) {
           if ( (*iter).getB().y() < curY) {
               edges.erase(iter);
           }else {
               ++iter;
           }
        }

   }
}
