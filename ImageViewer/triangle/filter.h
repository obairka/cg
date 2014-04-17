#ifndef FILTER_H
#define FILTER_H

#include <QPoint>
#include "texturedpoint.h"

class Filter
{
    int size;
    int type;
public:
    Filter(int size):size(size)
    {
        type = 0;
    }
    void setSize(int siz) {
        size = siz;
    }
    int getType() {
        return type;
    }

    virtual QPoint filter(const TexturedPoint& point) {
        int x = point.getTexX() * size;
        int y = point.getTexY() * size;
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x >= size) x = size-1;
        if (y >= size) y = size-1;
        return QPoint(x,y);
    }
};

#endif // FILTER_H
