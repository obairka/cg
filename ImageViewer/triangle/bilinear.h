#ifndef BILINEAR_H
#define BILINEAR_H


#include "filter.h"

class Texture;

class Bilinear : public Filter
{

public:
    Bilinear();
    virtual QColor filter(Texture* texture,const TexturedPoint& point);
};

#endif // BILINEAR_H
