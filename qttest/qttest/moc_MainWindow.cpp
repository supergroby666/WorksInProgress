/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created: Thu 21. Jun 08:16:35 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x09,
      29,   25,   11,   11, 0x09,
      45,   39,   11,   11, 0x09,
      63,   11,   11,   11, 0x09,
      72,   11,   11,   11, 0x09,
      79,   11,   11,   11, 0x09,
      86,   39,   11,   11, 0x09,
      97,   11,   11,   11, 0x09,
     111,   11,   11,   11, 0x09,
     125,   25,   11,   11, 0x09,
     135,   11,   11,   11, 0x09,
     142,   25,   11,   11, 0x09,
     152,   25,   11,   11, 0x09,
     162,   25,   11,   11, 0x09,
     172,   25,   11,   11, 0x09,
     182,   25,   11,   11, 0x09,
     192,   11,   11,   11, 0x09,
     202,   11,   11,   11, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0opendevice()\0val\0RFC(bool)\0"
    "index\0selectDevice(int)\0Header()\0"
    "Vars()\0data()\0speed(int)\0DataatSpeed()\0"
    "closeDevice()\0RTS(bool)\0Info()\0CB0(bool)\0"
    "CB1(bool)\0CB2(bool)\0CB3(bool)\0SPI(bool)\0"
    "SendSpi()\0CleanSpiText()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->opendevice(); break;
        case 1: _t->RFC((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->selectDevice((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->Header(); break;
        case 4: _t->Vars(); break;
        case 5: _t->data(); break;
        case 6: _t->speed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->DataatSpeed(); break;
        case 8: _t->closeDevice(); break;
        case 9: _t->RTS((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->Info(); break;
        case 11: _t->CB0((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->CB1((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->CB2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->CB3((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->SPI((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->SendSpi(); break;
        case 17: _t->CleanSpiText(); break;
        default: ;
        }
    }
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
    if (!strcmp(_clname, "Ui_MainWindow"))
        return static_cast< Ui_MainWindow*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
