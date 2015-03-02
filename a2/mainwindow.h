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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGenericMatrix>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pb_CreatePolygon_clicked();

    void on_m11_textChanged();
    void on_m12_textChanged();
    void on_m13_textChanged();
    void on_m21_textChanged();
    void on_m22_textChanged();
    void on_m23_textChanged();
    void on_m31_textChanged();
    void on_m32_textChanged();
    void on_m33_textChanged();

    //Stack Manipulation Buttons
    void on_pb_clearStack_clicked();
    void on_pb_pushMatrix_clicked();
    void on_pb_popMatrix_clicked();

    void on_pb_ClearPolygons_clicked();

private:
    Ui::MainWindow *ui;

    /**
     * @brief parseMatrix Attempt to parse the matrix input by users.
     * @return The matrix entered, or a Identity matrix if it failed.
     */
    QMatrix3x3 parseMatrix();

    /**
     * @brief updateResultMatrix given a matrix update the UI to show that matrix
     * in the result matrix grid.
     * @param matrix
     */
    void updateResultMatrix(QMatrix3x3 matrix);

    /**
     * @brief updateInputMatrix given a matrix update the UI to show the input matrix
     * in the input grid.
     * @param matrix
     */
    void updateInputMatrix(QMatrix3x3 matrix);

    /**
     * @brief updateCreatePolygonButton Update the CreatePolygon label with appropriate text.
     */
    void updateCreatePolygonButton();
};

#endif // MAINWINDOW_H
