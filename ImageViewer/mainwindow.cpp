#include <QObject>
#include <QDebug>
#include "mainwindow.h"
#include "square.h"

MainWindow::MainWindow(int w, int h, QWidget *parent)
    : QMainWindow(parent), drawPanel(w, h, this)
{
    int size = w<h?w:h;

    double xc = w*1.0/2.0;
    double yc = h*1.0/2.0;

    Square square(50, xc, yc );
    square.setMax(w,h);
    //square.draw(drawPanel);
    //square.rotate(40);
    //square.draw(drawPanel);

    square.scaleX(5);
    square.scaleY(5);

    //square.setCenter(100,100);
    square.draw(drawPanel);

    drawPanel.drawBresenhamLine(QPoint(xc, 0), QPoint(xc, h-1), Qt::black);

    drawPanel.drawBresenhamLine(QPoint(0, yc), QPoint(w-1, yc), Qt::black);


    setFixedSize(w,h);
    setCentralWidget(&drawPanel);
}
