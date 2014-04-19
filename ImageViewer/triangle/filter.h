#ifndef FILTER_H
#define FILTER_H

#include <QPoint>
#include "texturedpoint.h"
class Texture;
class Filter
{
protected:
    int type;

public:
    Filter();

    int getType();
    virtual QColor filter(Texture* texture, const TexturedPoint& point);
};

#endif // FILTER_H
