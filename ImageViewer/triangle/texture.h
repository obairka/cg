#ifndef TEXTURE_H
#define TEXTURE_H

#include <QColor>
#include "texturedpoint.h"

class Texture
{
public:
    Texture();
    QColor getColor(const TexturedPoint& point);
};

#endif // TEXTURE_H
