#include <QObject>
#include <QDebug>
#include "mainwindow.h"
#include "square.h"

MainWindow::MainWindow(int w, int h, QWidget *parent)
    : QMainWindow(parent), drawPanel(w, h, this),
      rotateContr(this,"ANGLE", 0, 360, 0),
      scaleXContr(this, "SCALE X", 0.1, 10, 1),
      scaleYContr(this, "SCALE Y", 1, 10, 1)
{
    int size = w<h?w:h;

    double xc = w*1.0/2.0;
    double yc = h*1.0/2.0;
    qDebug() << xc << yc;
    Square square(450, xc, yc );
    square.setMax(w,h);

    //square.draw(drawPanel);
    square.rotate(45);
    square.scaleX(0.8);
    square.scaleY(0.8);

    //square.setCenter(100,100);
    square.draw(drawPanel);

    drawPanel.drawBresenhamLine(QPoint(xc, 0), QPoint(xc, h-1), Qt::black);

    drawPanel.drawBresenhamLine(QPoint(0, yc), QPoint(w-1, yc), Qt::black);
/*
    QVBoxLayout* panelLayout = new QVBoxLayout(&drawPanelBox);
    panelLayout->addWidget(&drawPanel);
    drawPanelBox.setLayout(panelLayout);
    QVBoxLayout* cLayout = new QVBoxLayout(controllersBox);
    cLayout->addWidget(&rotateContr);
    cLayout->addWidget(&scaleXContr);
    cLayout->addWidget(&scaleYContr);
*/
    setFixedSize(w,h);
    setCentralWidget(&drawPanel);
}
