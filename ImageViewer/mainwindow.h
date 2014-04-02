#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawpanel.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    DrawPanel drawPanel;

public:
    MainWindow(int w, int h, QWidget *parent = 0);
    ~MainWindow() {}

};

#endif // MAINWINDOW_H
