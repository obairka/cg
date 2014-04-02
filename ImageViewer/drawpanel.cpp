#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include "drawpanel.h"

DrawPanel::DrawPanel(int w, int h,   QWidget *parent) :
    QWidget(parent),Canvas(w,h)
{
    setFixedSize(w, h);
}

void DrawPanel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawImage(0,0, image);
}


