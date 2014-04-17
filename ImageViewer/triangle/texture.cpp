#include <QObject>
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include "texture.h"

Texture::Texture(int max_size) : loaded (false), max_size(max_size)
{

}

void Texture::load(const std::string &image_src){
    QPixmap pixmap;
    pixmap.load(QObject::tr((image_src.c_str())));
    int width = pixmap.width();
    int height = pixmap.height();
    int size = width < height ? width : height;

    if (size > max_size) size = max_size;
    QImage raw_image = pixmap.toImage();
    image = raw_image.copy(0, 0, size, size);

    // TODO : crop to N*N
    loaded = true;
}

int Texture::getSize() const {
    return image.width();
}

bool Texture::isLoaded() const{
    return loaded;
}

QColor Texture::getColor(const TexturedPoint &point) {
    if (!loaded) {
        return Qt::black; // TODO:
    }

    // transform texX, texY to X,Y of image
    int x = point.getTexX() * image.width();
    int y =point.getTexY() * image.height();
    if (x< 0) x= 0;
    if (y< 0) y= 0;

    if (x>= image.width()) x= image.width()-1;
    if (y>= image.width()) y= image.width()-1;

    return QColor(image.pixel(x,y));
}
