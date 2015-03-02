/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Mar 2 11:32:22 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include "basicopenglview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    BasicOpenGLView *oglwidget;
    QGroupBox *groupBox;
    QPushButton *pb_ExitApp;
    QGroupBox *groupBox_2;
    QPushButton *pb_CreatePolygon;
    QPushButton *pb_ClearPolygons;
    QGroupBox *groupBox_3;
    QCheckBox *chbox_applyTransform;
    QGroupBox *groupBox_4;
    QPlainTextEdit *m11;
    QPlainTextEdit *m21;
    QPlainTextEdit *m31;
    QPlainTextEdit *m12;
    QPlainTextEdit *m22;
    QPlainTextEdit *m32;
    QPlainTextEdit *m13;
    QPlainTextEdit *m23;
    QPlainTextEdit *m33;
    QPushButton *pb_pushMatrix;
    QPushButton *pb_popMatrix;
    QGroupBox *groupBox_5;
    QPlainTextEdit *mr11;
    QPlainTextEdit *mr21;
    QPlainTextEdit *mr31;
    QPlainTextEdit *mr12;
    QPlainTextEdit *mr22;
    QPlainTextEdit *mr32;
    QPlainTextEdit *mr13;
    QPlainTextEdit *mr23;
    QPlainTextEdit *mr33;
    QPushButton *pb_clearStack;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(873, 709);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        oglwidget = new BasicOpenGLView(centralWidget);
        oglwidget->setObjectName(QString::fromUtf8("oglwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(oglwidget->sizePolicy().hasHeightForWidth());
        oglwidget->setSizePolicy(sizePolicy);
        oglwidget->setMinimumSize(QSize(400, 400));
        oglwidget->setLayoutDirection(Qt::LeftToRight);
        oglwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(192, 193, 186);"));

        gridLayout->addWidget(oglwidget, 0, 0, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setEnabled(true);
        groupBox->setMinimumSize(QSize(250, 200));
        groupBox->setMaximumSize(QSize(250, 16777215));
        pb_ExitApp = new QPushButton(groupBox);
        pb_ExitApp->setObjectName(QString::fromUtf8("pb_ExitApp"));
        pb_ExitApp->setGeometry(QRect(0, 590, 251, 41));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 20, 231, 91));
        pb_CreatePolygon = new QPushButton(groupBox_2);
        pb_CreatePolygon->setObjectName(QString::fromUtf8("pb_CreatePolygon"));
        pb_CreatePolygon->setGeometry(QRect(0, 20, 231, 41));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pb_CreatePolygon->sizePolicy().hasHeightForWidth());
        pb_CreatePolygon->setSizePolicy(sizePolicy1);
        pb_ClearPolygons = new QPushButton(groupBox_2);
        pb_ClearPolygons->setObjectName(QString::fromUtf8("pb_ClearPolygons"));
        pb_ClearPolygons->setGeometry(QRect(0, 50, 231, 41));
        sizePolicy1.setHeightForWidth(pb_ClearPolygons->sizePolicy().hasHeightForWidth());
        pb_ClearPolygons->setSizePolicy(sizePolicy1);
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 110, 231, 471));
        chbox_applyTransform = new QCheckBox(groupBox_3);
        chbox_applyTransform->setObjectName(QString::fromUtf8("chbox_applyTransform"));
        chbox_applyTransform->setGeometry(QRect(10, 40, 211, 21));
        chbox_applyTransform->setChecked(true);
        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 70, 211, 131));
        m11 = new QPlainTextEdit(groupBox_4);
        m11->setObjectName(QString::fromUtf8("m11"));
        m11->setGeometry(QRect(20, 30, 51, 21));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        m11->setFont(font);
        m11->setFocusPolicy(Qt::WheelFocus);
        m11->setFrameShadow(QFrame::Plain);
        m11->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m11->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m21 = new QPlainTextEdit(groupBox_4);
        m21->setObjectName(QString::fromUtf8("m21"));
        m21->setGeometry(QRect(20, 60, 51, 21));
        m21->setFont(font);
        m21->setFocusPolicy(Qt::WheelFocus);
        m21->setFrameShadow(QFrame::Plain);
        m21->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m21->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m31 = new QPlainTextEdit(groupBox_4);
        m31->setObjectName(QString::fromUtf8("m31"));
        m31->setEnabled(false);
        m31->setGeometry(QRect(20, 90, 51, 21));
        m31->setFont(font);
        m31->setFocusPolicy(Qt::WheelFocus);
        m31->setFrameShadow(QFrame::Plain);
        m31->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m31->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m12 = new QPlainTextEdit(groupBox_4);
        m12->setObjectName(QString::fromUtf8("m12"));
        m12->setGeometry(QRect(80, 30, 51, 21));
        m12->setFont(font);
        m12->setFocusPolicy(Qt::WheelFocus);
        m12->setFrameShadow(QFrame::Plain);
        m12->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m12->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m22 = new QPlainTextEdit(groupBox_4);
        m22->setObjectName(QString::fromUtf8("m22"));
        m22->setGeometry(QRect(80, 60, 51, 21));
        m22->setFont(font);
        m22->setFocusPolicy(Qt::WheelFocus);
        m22->setFrameShadow(QFrame::Plain);
        m22->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m22->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m32 = new QPlainTextEdit(groupBox_4);
        m32->setObjectName(QString::fromUtf8("m32"));
        m32->setEnabled(false);
        m32->setGeometry(QRect(80, 90, 51, 21));
        m32->setFont(font);
        m32->setFocusPolicy(Qt::WheelFocus);
        m32->setFrameShadow(QFrame::Plain);
        m32->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m32->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m13 = new QPlainTextEdit(groupBox_4);
        m13->setObjectName(QString::fromUtf8("m13"));
        m13->setGeometry(QRect(140, 30, 51, 21));
        m13->setFont(font);
        m13->setFocusPolicy(Qt::WheelFocus);
        m13->setFrameShadow(QFrame::Plain);
        m13->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m13->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m23 = new QPlainTextEdit(groupBox_4);
        m23->setObjectName(QString::fromUtf8("m23"));
        m23->setGeometry(QRect(140, 60, 51, 21));
        m23->setFont(font);
        m23->setFocusPolicy(Qt::WheelFocus);
        m23->setFrameShadow(QFrame::Plain);
        m23->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m23->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m33 = new QPlainTextEdit(groupBox_4);
        m33->setObjectName(QString::fromUtf8("m33"));
        m33->setEnabled(false);
        m33->setGeometry(QRect(140, 90, 51, 21));
        m33->setFont(font);
        m33->setFocusPolicy(Qt::WheelFocus);
        m33->setFrameShadow(QFrame::Plain);
        m33->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m33->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pb_pushMatrix = new QPushButton(groupBox_3);
        pb_pushMatrix->setObjectName(QString::fromUtf8("pb_pushMatrix"));
        pb_pushMatrix->setGeometry(QRect(10, 210, 111, 41));
        pb_popMatrix = new QPushButton(groupBox_3);
        pb_popMatrix->setObjectName(QString::fromUtf8("pb_popMatrix"));
        pb_popMatrix->setGeometry(QRect(110, 210, 111, 41));
        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 270, 211, 131));
        mr11 = new QPlainTextEdit(groupBox_5);
        mr11->setObjectName(QString::fromUtf8("mr11"));
        mr11->setEnabled(false);
        mr11->setGeometry(QRect(20, 30, 51, 21));
        mr11->setFont(font);
        mr11->setFocusPolicy(Qt::NoFocus);
        mr11->setFrameShadow(QFrame::Plain);
        mr11->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mr11->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mr21 = new QPlainTextEdit(groupBox_5);
        mr21->setObjectName(QString::fromUtf8("mr21"));
        mr21->setEnabled(false);
        mr21->setGeometry(QRect(20, 60, 51, 21));
        mr21->setFont(font);
        mr21->setFocusPolicy(Qt::NoFocus);
        mr21->setFrameShadow(QFrame::Plain);
        mr21->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mr21->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mr31 = new QPlainTextEdit(groupBox_5);
        mr31->setObjectName(QString::fromUtf8("mr31"));
        mr31->setEnabled(false);
        mr31->setGeometry(QRect(20, 90, 51, 21));
        mr31->setFont(font);
        mr31->setFocusPolicy(Qt::NoFocus);
        mr31->setFrameShadow(QFrame::Plain);
        mr31->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mr31->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mr12 = new QPlainTextEdit(groupBox_5);
        mr12->setObjectName(QString::fromUtf8("mr12"));
        mr12->setEnabled(false);
        mr12->setGeometry(QRect(80, 30, 51, 21));
        mr12->setFont(font);
        mr12->setFocusPolicy(Qt::NoFocus);
        mr12->setFrameShadow(QFrame::Plain);
        mr12->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mr12->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mr22 = new QPlainTextEdit(groupBox_5);
        mr22->setObjectName(QString::fromUtf8("mr22"));
        mr22->setEnabled(false);
        mr22->setGeometry(QRect(80, 60, 51, 21));
        mr22->setFont(font);
        mr22->setFocusPolicy(Qt::NoFocus);
        mr22->setFrameShadow(QFrame::Plain);
        mr22->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mr22->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mr32 = new QPlainTextEdit(groupBox_5);
        mr32->setObjectName(QString::fromUtf8("mr32"));
        mr32->setEnabled(false);
        mr32->setGeometry(QRect(80, 90, 51, 21));
        mr32->setFont(font);
        mr32->setFocusPolicy(Qt::NoFocus);
        mr32->setFrameShadow(QFrame::Plain);
        mr32->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mr32->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mr13 = new QPlainTextEdit(groupBox_5);
        mr13->setObjectName(QString::fromUtf8("mr13"));
        mr13->setEnabled(false);
        mr13->setGeometry(QRect(140, 30, 51, 21));
        mr13->setFont(font);
        mr13->setFocusPolicy(Qt::NoFocus);
        mr13->setFrameShadow(QFrame::Plain);
        mr13->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mr13->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mr23 = new QPlainTextEdit(groupBox_5);
        mr23->setObjectName(QString::fromUtf8("mr23"));
        mr23->setEnabled(false);
        mr23->setGeometry(QRect(140, 60, 51, 21));
        mr23->setFont(font);
        mr23->setFocusPolicy(Qt::NoFocus);
        mr23->setFrameShadow(QFrame::Plain);
        mr23->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mr23->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mr33 = new QPlainTextEdit(groupBox_5);
        mr33->setObjectName(QString::fromUtf8("mr33"));
        mr33->setEnabled(false);
        mr33->setGeometry(QRect(140, 90, 51, 21));
        mr33->setFont(font);
        mr33->setFocusPolicy(Qt::NoFocus);
        mr33->setFrameShadow(QFrame::Plain);
        mr33->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mr33->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pb_clearStack = new QPushButton(groupBox_3);
        pb_clearStack->setObjectName(QString::fromUtf8("pb_clearStack"));
        pb_clearStack->setGeometry(QRect(60, 240, 111, 41));

        gridLayout->addWidget(groupBox, 0, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 873, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(pb_ExitApp, SIGNAL(clicked()), MainWindow, SLOT(close()));
        QObject::connect(chbox_applyTransform, SIGNAL(toggled(bool)), oglwidget, SLOT(toggleMatrixApplication(bool)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Controls", 0, QApplication::UnicodeUTF8));
        pb_ExitApp->setText(QApplication::translate("MainWindow", "Quit Application", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Polygons", 0, QApplication::UnicodeUTF8));
        pb_CreatePolygon->setText(QApplication::translate("MainWindow", "Create Polygon", 0, QApplication::UnicodeUTF8));
        pb_ClearPolygons->setText(QApplication::translate("MainWindow", "Clear Polygons", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Transformations", 0, QApplication::UnicodeUTF8));
        chbox_applyTransform->setText(QApplication::translate("MainWindow", "Apply Transformations", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "New Matrix", 0, QApplication::UnicodeUTF8));
        m11->setPlainText(QApplication::translate("MainWindow", "1\n"
"", 0, QApplication::UnicodeUTF8));
        m21->setPlainText(QApplication::translate("MainWindow", "0\n"
"", 0, QApplication::UnicodeUTF8));
        m31->setPlainText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        m12->setPlainText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        m22->setPlainText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        m32->setPlainText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        m13->setPlainText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        m23->setPlainText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        m33->setPlainText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        pb_pushMatrix->setText(QApplication::translate("MainWindow", "Push", 0, QApplication::UnicodeUTF8));
        pb_popMatrix->setText(QApplication::translate("MainWindow", "Pop", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Resulting Transform", 0, QApplication::UnicodeUTF8));
        mr11->setPlainText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        mr21->setPlainText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        mr31->setPlainText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        mr12->setPlainText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        mr22->setPlainText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        mr32->setPlainText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        mr13->setPlainText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        mr23->setPlainText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        mr33->setPlainText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        pb_clearStack->setText(QApplication::translate("MainWindow", "Clear Stack", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
