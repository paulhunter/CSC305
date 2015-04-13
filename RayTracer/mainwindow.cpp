#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "unistd.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "Main: Creating Ray Tracer";
    this->rt = new RayTracer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->ui->image->setPixmap(QPixmap::fromImage(*(rt->image)));
}
