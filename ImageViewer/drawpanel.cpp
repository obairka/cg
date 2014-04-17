#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include "drawpanel.h"

DrawPanel::DrawPanel(int w, int h,   QWidget *parent) :
    QWidget(parent),Canvas(w,h),square(w,w/2,h/2), texture(w)
{
    texture.load("homer.png");
    setFixedSize(w, h);
    square.setSize(texture.getSize());

    square.setMax(w,h);
    QObject::connect(&square, SIGNAL(angleChanged(double)), this, SLOT(repaint_square()));
    QObject::connect(&square, SIGNAL(scaleXChanged(double)), this, SLOT(repaint_square()));
    QObject::connect(&square, SIGNAL(scaleYChanged(double)), this, SLOT(repaint_square()));

    square.draw(*this, &texture);
}

void DrawPanel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawImage(0,0, image);
}

void DrawPanel::open(const std::string& filename){
    texture.load(filename);
 //TODO: square.deafult();
    square.setSize(texture.getSize());
    square.setCenter(Canvas::width/2., Canvas::height/2.);
    square.rotate(0);
    square.scaleX(1);
    square.scaleY(1);
    repaint_square();
}

void DrawPanel::repaint_square(){
    square.draw(*this, &texture);
    repaint();
}

