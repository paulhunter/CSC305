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

/* ********* POLYGON Actions ************* */
void MainWindow::updateCreatePolygonButton()
{
    if(ui->oglwidget->Drawing())
    {
        ui->pb_CreatePolygon->setText("Finish Polygon");
    }
    else
    {
        ui->pb_CreatePolygon->setText("Create Polygon");
    }
}

void MainWindow::on_pb_CreatePolygon_clicked()
{
    ui->oglwidget->togglePolygonDraw();
    updateCreatePolygonButton();
}

void MainWindow::on_pb_ClearPolygons_clicked()
{
    ui->oglwidget->clearAllPolygons();
    updateCreatePolygonButton();
}

/* ************* MATRIX Actions ************ */
void MainWindow::on_pb_pushMatrix_clicked()
{
    //Push the created matrix onto the stack.
    QMatrix3x3 n = parseMatrix();
    QMatrix3x3 i = QMatrix3x3();
    i.setToIdentity();
    if(n == i)
    {
        //If the matrix given was the identity, either the user
        //input it, or the parse failed, in either case, we don't
        //waste time applying identities.
    }
    else
    {
        //Otherwise, push the new matrix onto the stack, refresh
        //input matrix to an identity, and update the result matrix.
        updateInputMatrix(i);
        i = this->ui->oglwidget->PushMatrix(n);
        updateResultMatrix(i);
    }
}


void MainWindow::on_pb_popMatrix_clicked()
{
    QMatrix3x3 r = this->ui->oglwidget->PopMatrix();
    QMatrix3x3 i;
    i.setToIdentity();
    if(r == i)
    {
        //If we are returning an identity, the stack is empty.
        //Don't update the Input matrix.
    }
    else
    {
        //Else, we have removed something, so update that input matrix
        //and result matrix.
        updateInputMatrix(r);
        updateResultMatrix(this->ui->oglwidget->CurrentTransform());
    }
}

void MainWindow::on_pb_clearStack_clicked()
{
    this->ui->oglwidget->ClearMatrixStack();
    QMatrix3x3 r;
    r.setToIdentity();
    updateResultMatrix(r);
}

QMatrix3x3 MainWindow::parseMatrix()
{
    QMatrix3x3 result = QMatrix3x3();
    QPlainTextEdit *faulty;
    bool ok;

    do
    {
        faulty = this->ui->m11;
        result.operator ()(0,0) = faulty->toPlainText().toDouble(&ok);
        if(!ok) break;

        faulty = this->ui->m12;
        result.operator ()(0,1) = faulty->toPlainText().toDouble(&ok);
        if(!ok) break;

        faulty = this->ui->m13;
        result.operator ()(0,2) = faulty->toPlainText().toDouble(&ok);
        if(!ok) break;

        faulty = this->ui->m21;
        result.operator ()(1,0) = faulty->toPlainText().toDouble(&ok);
        if(!ok) break;

        faulty = this->ui->m22;
        result.operator ()(1,1) = faulty->toPlainText().toDouble(&ok);
        if(!ok) break;

        faulty = this->ui->m23;
        result.operator ()(1,2) = faulty->toPlainText().toDouble(&ok);
        if(!ok) break;

        faulty = this->ui->m31;
        result.operator ()(2,0) = faulty->toPlainText().toDouble(&ok);
        if(!ok) break;

        faulty = this->ui->m32;
        result.operator ()(2,1) = faulty->toPlainText().toDouble(&ok);
        if(!ok) break;

        faulty = this->ui->m33;
        result.operator ()(2,2) = faulty->toPlainText().toDouble(&ok);
        if(!ok) break;
    } while (false);

    if(!ok)
    {
        //One of the parsings failed. Focus on the textbox that failed.
        QPalette p = faulty->palette();
        p.setColor(QPalette::Active, QPalette::Base, Qt::red);
        p.setColor(QPalette::Inactive, QPalette::Base, Qt::red);
        faulty->setPalette(p);
        faulty->setFocus();
        result.setToIdentity();
    }
    return result;
}

void MainWindow::updateInputMatrix(QMatrix3x3 matrix)
{
    this->ui->m11->setPlainText(QString::number(matrix.operator ()(0,0)));
    this->ui->m12->setPlainText(QString::number(matrix.operator ()(0,1)));
    this->ui->m13->setPlainText(QString::number(matrix.operator ()(0,2)));
    this->ui->m21->setPlainText(QString::number(matrix.operator ()(1,0)));
    this->ui->m22->setPlainText(QString::number(matrix.operator ()(1,1)));
    this->ui->m23->setPlainText(QString::number(matrix.operator ()(1,2)));
    this->ui->m31->setPlainText(QString::number(matrix.operator ()(2,0)));
    this->ui->m32->setPlainText(QString::number(matrix.operator ()(2,1)));
    this->ui->m33->setPlainText(QString::number(matrix.operator ()(2,2)));
}

void MainWindow::updateResultMatrix(QMatrix3x3 matrix)
{
    this->ui->mr11->setPlainText(QString::number(matrix.operator ()(0,0)));
    this->ui->mr12->setPlainText(QString::number(matrix.operator ()(0,1)));
    this->ui->mr13->setPlainText(QString::number(matrix.operator ()(0,2)));
    this->ui->mr21->setPlainText(QString::number(matrix.operator ()(1,0)));
    this->ui->mr22->setPlainText(QString::number(matrix.operator ()(1,1)));
    this->ui->mr23->setPlainText(QString::number(matrix.operator ()(1,2)));
    this->ui->mr31->setPlainText(QString::number(matrix.operator ()(2,0)));
    this->ui->mr32->setPlainText(QString::number(matrix.operator ()(2,1)));
    this->ui->mr33->setPlainText(QString::number(matrix.operator ()(2,2)));
}

/* ************ INPUT Changed Handlers ********************/
// These handlers will reset the palette of the textboxes to white after
// they were reddened by the validation process
void MainWindow::on_m11_textChanged()
{
    QPalette p = this->ui->m11->palette();
    p.setColor(QPalette::Active, QPalette::Base, Qt::white);
    p.setColor(QPalette::Inactive, QPalette::Base, Qt::white);
    this->ui->m11->setPalette(p);
}

void MainWindow::on_m12_textChanged()
{
    QPalette p = this->ui->m12->palette();
    p.setColor(QPalette::Active, QPalette::Base, Qt::white);
    p.setColor(QPalette::Inactive, QPalette::Base, Qt::white);
    this->ui->m12->setPalette(p);
}

void MainWindow::on_m13_textChanged()
{
    QPalette p = this->ui->m13->palette();
    p.setColor(QPalette::Active, QPalette::Base, Qt::white);
    p.setColor(QPalette::Inactive, QPalette::Base, Qt::white);
    this->ui->m13->setPalette(p);
}

void MainWindow::on_m21_textChanged()
{
    QPalette p = this->ui->m21->palette();
    p.setColor(QPalette::Active, QPalette::Base, Qt::white);
    p.setColor(QPalette::Inactive, QPalette::Base, Qt::white);
    this->ui->m21->setPalette(p);
}

void MainWindow::on_m22_textChanged()
{
    QPalette p = this->ui->m22->palette();
    p.setColor(QPalette::Active, QPalette::Base, Qt::white);
    p.setColor(QPalette::Inactive, QPalette::Base, Qt::white);
    this->ui->m22->setPalette(p);
}

void MainWindow::on_m23_textChanged()
{
    QPalette p = this->ui->m23->palette();
    p.setColor(QPalette::Active, QPalette::Base, Qt::white);
    p.setColor(QPalette::Inactive, QPalette::Base, Qt::white);
    this->ui->m23->setPalette(p);
}


void MainWindow::on_m31_textChanged()
{
    QPalette p = this->ui->m31->palette();
    p.setColor(QPalette::Active, QPalette::Base, Qt::white);
    p.setColor(QPalette::Inactive, QPalette::Base, Qt::white);
    this->ui->m31->setPalette(p);
}

void MainWindow::on_m32_textChanged()
{
    QPalette p = this->ui->m32->palette();
    p.setColor(QPalette::Active, QPalette::Base, Qt::white);
    p.setColor(QPalette::Inactive, QPalette::Base, Qt::white);
    this->ui->m32->setPalette(p);
}

void MainWindow::on_m33_textChanged()
{
    QPalette p = this->ui->m33->palette();
    p.setColor(QPalette::Active, QPalette::Base, Qt::white);
    p.setColor(QPalette::Inactive, QPalette::Base, Qt::white);
    this->ui->m33->setPalette(p);
}


