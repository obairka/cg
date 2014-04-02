#include <QObject>
#include <QDebug>
#include "mainwindow.h"
#include "triangle/texturedpoint.h"
#include "triangle/triangle.h"
MainWindow::MainWindow(int w, int h, QWidget *parent)
    : QMainWindow(parent), drawPanel(w, h, this)
{

    TexturedPoint a (200, 20, 0, 0);
    TexturedPoint b (200, 300, 0, 1);
    TexturedPoint c (300, 300, 1, 1);

    Triangle triangle(b, a, c);
    drawPanel.Canvas::clear();
    triangle.draw(drawPanel);
    triangle.rotate(90);
    triangle.draw(drawPanel);

    setFixedSize(w,h);
    setCentralWidget(&drawPanel);
}
