#ifndef DRAWPANEL_H
#define DRAWPANEL_H

#include <QWidget>
#include <QPoint>
#include "canvas.h"

class DrawPanel : public QWidget, public Canvas
{
    Q_OBJECT
public:
    explicit DrawPanel( int w, int h,   QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);


};

#endif // DRAWPANEL_H
