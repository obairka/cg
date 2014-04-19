#ifndef TEXTURE_H
#define TEXTURE_H

#include <QPoint>
#include "filter.h"
#include "bilinear.h"
#include <QImage>
#include <QColor>
#include <QObject>
#include "texturedpoint.h"


class Texture : public QObject
{
    Q_OBJECT
    static Filter simpleFilter;
    static Bilinear bilinearFilter;
    Filter* filter;
    QImage image;
    bool loaded;
    int max_size;
public slots:
    void setFilter(int filterType);
public:

    Texture(int max_size);

    void load(const std::string& image_src);
    bool isLoaded() const;
    int getSize() const;
    QColor getColor(const TexturedPoint& point);
    QColor getColor(const QPoint& point);

};

#endif // TEXTURE_H
