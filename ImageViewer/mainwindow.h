#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawpanel.h"
#include "sizecontroller.h"
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QGroupBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    DrawPanel* drawPanel;
public:
    MainWindow(int w, int h, QWidget *parent = 0);
    ~MainWindow() {}
public slots:
    void openClicked(bool  );


};

#endif // MAINWINDOW_H
