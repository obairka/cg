#ifndef TEXTURE_H
#define TEXTURE_H

#include <QImage>
#include <QColor>
#include "texturedpoint.h"

class Texture
{
    QImage image;
    bool loaded;
    int max_size;
public:
    Texture(int max_size);
    // open image
    void load(const std::string& image_src);
    QColor getColor(const TexturedPoint& point);
    bool isLoaded() const;
    int getSize() const;
};

#endif // TEXTURE_H
