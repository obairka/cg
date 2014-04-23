#ifndef MIPMAPPER_H
#define MIPMAPPER_H

#include "filter.h"
#include "bilinear.h"
#include "texture/texturedpoint.h"
#include <QColor>

class Texture;

class Mipmapper : public Filter
{
private:
    QColor bilinear(Texture* texture, const TexturedPoint& point, int level);
public:
    Mipmapper();
    QColor filter(Texture* texture, const TexturedPoint& point );
};

#endif // MIPMAPPER_H
