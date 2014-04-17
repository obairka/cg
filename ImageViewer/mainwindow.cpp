#include <QObject>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mainwindow.h"
#include "square.h"



MainWindow::MainWindow(int w, int h, QWidget *parent)
    : QMainWindow(parent)
{

    drawPanel = new DrawPanel(w,h, this);
    SizeController* rotateContr = new SizeController(this, "ANGLE",  0, 360, 0);
    SizeController* scaleXContr= new SizeController(this, "SCALE X", 0.1, 10, 1);
    SizeController* scaleYContr= new SizeController(this, "SCALE Y", 0.1, 10, 1);
    QGroupBox* controllersBox = new QGroupBox(this);
    QGroupBox* drawPanelBox= new QGroupBox(this);


    QObject::connect(&drawPanel->getSquare(), SIGNAL(angleChanged(double)), rotateContr, SLOT(setValue(double)));
    QObject::connect(rotateContr, SIGNAL(valueChanged(double)), &drawPanel->getSquare(), SLOT(rotate(double)));
    QObject::connect(&drawPanel->getSquare(), SIGNAL(scaleXChanged(double)), scaleXContr, SLOT(setValue(double)));
    QObject::connect(&drawPanel->getSquare(), SIGNAL(scaleYChanged(double)), scaleYContr, SLOT(setValue(double)));
    QObject::connect(scaleXContr,SIGNAL(valueChanged(double)), &drawPanel->getSquare(), SLOT(scaleX(double)));
    QObject::connect(scaleYContr,SIGNAL(valueChanged(double)), &drawPanel->getSquare(), SLOT(scaleY(double)));

    QVBoxLayout* panelLayout = new QVBoxLayout();
    panelLayout->addWidget(drawPanel);
    drawPanelBox->setLayout(panelLayout);
    drawPanelBox->setFixedSize(w, h);
    drawPanelBox->setMinimumSize(w,h);
    panelLayout->setSizeConstraint(QLayout::SetFixedSize);
    drawPanelBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QVBoxLayout* cLayout = new QVBoxLayout();
    cLayout->addWidget(rotateContr);
    cLayout->addWidget(scaleXContr);
    cLayout->addWidget(scaleYContr);
    controllersBox->setLayout(cLayout);
    cLayout->setSizeConstraint(QLayout::SetFixedSize);
    controllersBox->setMinimumSize(250, h);
    controllersBox->setFixedSize(250, h);
    controllersBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QWidget * center = new QWidget(this);
    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(drawPanelBox);
    hlayout->addWidget(controllersBox);
    hlayout->setSizeConstraint(QLayout::SetFixedSize);
    center->setMinimumSize(w+300, h);
    center->setFixedSize(w+300, h);
    center->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    center->setLayout(hlayout);

    QMenuBar *menuBar = new QMenuBar(this);
    QMenu* menu = new QMenu(tr("File"), menuBar);
    QAction* openAction = menu->addAction(tr("Open"));

    QObject::connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openClicked(bool)));


    menuBar->addMenu(menu);

    this->setMenuBar(menuBar);

    setCentralWidget(center);
}


void MainWindow::openClicked(bool)
{
    // TODO:
    // open dialog
    QFileDialog fileDialog(this);
    fileDialog.deleteLater();
    fileDialog.setFileMode( QFileDialog::ExistingFile);
    fileDialog.setNameFilter(tr("*.png"));
    QStringList fileNames;
    if (fileDialog.exec())
        fileNames = fileDialog.selectedFiles();
    else {
        return;
    }
    try {
        drawPanel->open(fileNames.at(0).toStdString());
    } catch(...) {
        // TODO:

    }

}
