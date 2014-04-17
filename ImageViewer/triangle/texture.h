#ifndef TEXTURE_H
#define TEXTURE_H

#include "filter.h"
#include <QImage>
#include <QColor>
#include "texturedpoint.h"

class Texture
{
    static Filter simpleFilter;
    Filter* filter;
    QImage image;
    bool loaded;
    int max_size;
public:
    Texture(int max_size);
    void setFilter(int filterType);
    void load(const std::string& image_src);
    bool isLoaded() const;
    int getSize() const;
    QColor getColor(const TexturedPoint& point);

};

#endif // TEXTURE_H
