#include <QObject>
#include "texture.h"

Texture::Texture() : loaded (false)
{
}

void Texture::load(const std::string &image_src){
    /*QPixmap pixmap;
    pixmap.load(QObject::tr((image_src)));
    this->image = pixmap.toImage();
    // TODO : crop to N*N
    loaded = true;*/
}

bool Texture::isLoaded() const{
    return loaded;
}

QColor Texture::getColor(const TexturedPoint &point) {
    if (!loaded) {
        return Qt::black; // TODO:
    }
    // transform texX, texY to X,Y of image
}
