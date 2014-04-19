#include <QObject>
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include "texture.h"

Filter Texture::simpleFilter;
Bilinear Texture::bilinearFilter;

Texture::Texture(int max_size) : filter(0), loaded (false), max_size(max_size)
{
    filter = &bilinearFilter;

}

QColor Texture::getColor(const QPoint& point){
    if (isLoaded()) {

        return image.pixel(point);
    }
    //TODO:
    return Qt::black;
}

void Texture::setFilter(const int filterType)
{
    if (filter->getType() == filterType) return;

    if (filterType == simpleFilter.getType()) {
        filter = &simpleFilter;
    }
    else if (filterType == bilinearFilter.getType()) {
        filter = &bilinearFilter;
    } else {
        // TODO
    }
}

void Texture::load(const std::string &image_src) {
    QPixmap pixmap;
    pixmap.load(QObject::tr((image_src.c_str())));

    int width = pixmap.width();
    int height = pixmap.height();
    int size = width < height ? width : height;
    if (size > max_size) size = max_size;

    QImage raw_image = pixmap.toImage();
    image = raw_image.copy(0, 0, size, size);

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
    // TODO : ADD Filtration
    return filter->filter(this,point);
}
