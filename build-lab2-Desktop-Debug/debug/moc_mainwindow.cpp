/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Mon Mar 2 11:32:27 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../a2/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      42,   11,   11,   11, 0x08,
      63,   11,   11,   11, 0x08,
      84,   11,   11,   11, 0x08,
     105,   11,   11,   11, 0x08,
     126,   11,   11,   11, 0x08,
     147,   11,   11,   11, 0x08,
     168,   11,   11,   11, 0x08,
     189,   11,   11,   11, 0x08,
     210,   11,   11,   11, 0x08,
     231,   11,   11,   11, 0x08,
     258,   11,   11,   11, 0x08,
     285,   11,   11,   11, 0x08,
     311,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_pb_CreatePolygon_clicked()\0"
    "on_m11_textChanged()\0on_m12_textChanged()\0"
    "on_m13_textChanged()\0on_m21_textChanged()\0"
    "on_m22_textChanged()\0on_m23_textChanged()\0"
    "on_m31_textChanged()\0on_m32_textChanged()\0"
    "on_m33_textChanged()\0on_pb_clearStack_clicked()\0"
    "on_pb_pushMatrix_clicked()\0"
    "on_pb_popMatrix_clicked()\0"
    "on_pb_ClearPolygons_clicked()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_pb_CreatePolygon_clicked(); break;
        case 1: _t->on_m11_textChanged(); break;
        case 2: _t->on_m12_textChanged(); break;
        case 3: _t->on_m13_textChanged(); break;
        case 4: _t->on_m21_textChanged(); break;
        case 5: _t->on_m22_textChanged(); break;
        case 6: _t->on_m23_textChanged(); break;
        case 7: _t->on_m31_textChanged(); break;
        case 8: _t->on_m32_textChanged(); break;
        case 9: _t->on_m33_textChanged(); break;
        case 10: _t->on_pb_clearStack_clicked(); break;
        case 11: _t->on_pb_pushMatrix_clicked(); break;
        case 12: _t->on_pb_popMatrix_clicked(); break;
        case 13: _t->on_pb_ClearPolygons_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
