#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "Main: Creating Ray Tracer";
    RayTracer rt = RayTracer();
    qDebug() << "Main: Rendering...";
    //QImage toDisplay = rt.render(this->ui->image->width(), this->ui->image->height());

    //this->ui->image->setPixmap(QPixmap::fromImage(toDisplay));
}

MainWindow::~MainWindow()
{
    delete ui;
}
