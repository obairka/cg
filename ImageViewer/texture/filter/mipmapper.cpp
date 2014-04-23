#include "mipmapper.h"
#include "texture/texture.h"
#include <QDebug>

Mipmapper::Mipmapper()
{
    this->type = 2;
}

QColor Mipmapper::filter(Texture *texture, const TexturedPoint &point ){


    double dsdp = point.get_tex_in_pixX()/texture->get_texel_size();
    double dtdp = point.get_tex_in_pixY()/texture->get_texel_size();

    int level = fabs(sqrt(pow(dsdp,2)+pow(dtdp,2)) );
    if (level >= texture->get_LODs_count()) {
        level = texture->get_LODs_count()-1;
    }

    return bilinear(texture, point, level);
}

QColor Mipmapper::bilinear(Texture* texture, const TexturedPoint& point, int level){
    int size = texture->get_LOD(level).width();
    if (!texture)
        return QColor();
    double fx = point.getTexX() * size;
    double fy = point.getTexY() * size;

    if (fx >= size) fx =size-1;
    if (fy >= size) fy =size-1;
    if (fx < 0) fx = 0;
    if (fy < 0) fy = 0;
    int ix = fx;
    int iy = fy;
    fx = fx - ix;
    fy = fy - iy;

    double x_opp = fx;
    double y_opp = fy;
    fx = 1. - x_opp;
    fy = 1. - y_opp;

    const QImage& LOD = texture->get_LOD(level);
    if (ix != size -1 && iy != size -1 ){

        QColor p1 = LOD.pixel(ix  , iy);
        QColor p2 = LOD.pixel(ix+1, iy);
        QColor p3 = LOD.pixel(ix  , iy+1);
        QColor p4 = LOD.pixel(ix+1, iy+1);

        QColor a, b, c;

        a.setRed( p2.red() * x_opp + p1.red()*fx);
        b.setRed( p4.red() * x_opp + p3.red()*fx);
        c.setRed(b.red()*y_opp + a.red()*fy);

        a.setGreen( p2.green() * x_opp + p1.green()*fx);
        b.setGreen( p4.green() * x_opp + p3.green()*fx);
        c.setGreen(b.green()*y_opp + a.green()*fy);

        a.setBlue( p2.blue() * x_opp + p1.blue()*fx);
        b.setBlue( p4.blue() * x_opp + p3.blue()*fx);
        c.setBlue(b.blue()*y_opp + a.blue()*fy);

        return c;
    }

    return LOD.pixel(ix, iy);
}
