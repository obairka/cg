#include "filter.h"
#include "texture.h"
#include <QDebug>
Filter::Filter( )
{
    type = 0;
}

int Filter::getType() {
    return type;
}


QColor Filter::filter(Texture* texture,const TexturedPoint& point) {

    int size = texture->getSize();
    int x = point.getTexX() * size;
    int y = point.getTexY() * size  ;
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x >= size) x = size-1;
    if (y >= size) y = size-1;
    return texture->getColor(QPoint(x,y));
}
