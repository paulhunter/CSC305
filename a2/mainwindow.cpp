/*
 * mainwindow.h
 *
 * Created by: Brian Wyvill
 * Last Author: Paul Hunter
 *
 * CSC 305 - Assignment 1 - Homogeneous Coordinates and Matrices
 *
 * Application window, contains all UI handlers not completed using slots/signals.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "unistd.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// ///////////////////////////////////////
// VIEW POINT BUTTON CLICK HANDLERS
// ////////////////////////////////////////
void MainWindow::on_pushButton_clicked()
{
    this->ui->oglwidget->SetCameraPosition(0.0, 1.57/3.0, 50.0);
}

void MainWindow::on_pushButton_2_clicked()
{
     this->ui->oglwidget->SetCameraPosition(1.57/2.0, 1.57/2.0, 50.0);
}

void MainWindow::on_pushButton_3_clicked()
{
     this->ui->oglwidget->SetCameraPosition(2.60, 1.57/5.0, 50.0);
}
