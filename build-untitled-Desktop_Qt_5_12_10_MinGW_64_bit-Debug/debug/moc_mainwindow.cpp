/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../untitled/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[263];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "onNewInstance"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 12), // "onInsertHead"
QT_MOC_LITERAL(4, 39, 12), // "onInsertTail"
QT_MOC_LITERAL(5, 52, 10), // "onDeleteAt"
QT_MOC_LITERAL(6, 63, 18), // "onNewStackInstance"
QT_MOC_LITERAL(7, 82, 6), // "onPush"
QT_MOC_LITERAL(8, 89, 5), // "onPop"
QT_MOC_LITERAL(9, 95, 20), // "onTraverseLinkedList"
QT_MOC_LITERAL(10, 116, 26), // "onNewCircularQueueInstance"
QT_MOC_LITERAL(11, 143, 32), // "onNewCustomCapacityQueueInstance"
QT_MOC_LITERAL(12, 176, 9), // "onEnqueue"
QT_MOC_LITERAL(13, 186, 9), // "onDequeue"
QT_MOC_LITERAL(14, 196, 12), // "onScreenshot"
QT_MOC_LITERAL(15, 209, 12), // "onSaveToFile"
QT_MOC_LITERAL(16, 222, 14), // "onLoadFromFile"
QT_MOC_LITERAL(17, 237, 19), // "onTabCloseRequested"
QT_MOC_LITERAL(18, 257, 5) // "index"

    },
    "MainWindow\0onNewInstance\0\0onInsertHead\0"
    "onInsertTail\0onDeleteAt\0onNewStackInstance\0"
    "onPush\0onPop\0onTraverseLinkedList\0"
    "onNewCircularQueueInstance\0"
    "onNewCustomCapacityQueueInstance\0"
    "onEnqueue\0onDequeue\0onScreenshot\0"
    "onSaveToFile\0onLoadFromFile\0"
    "onTabCloseRequested\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    0,  102,    2, 0x08 /* Private */,
      11,    0,  103,    2, 0x08 /* Private */,
      12,    0,  104,    2, 0x08 /* Private */,
      13,    0,  105,    2, 0x08 /* Private */,
      14,    0,  106,    2, 0x08 /* Private */,
      15,    0,  107,    2, 0x08 /* Private */,
      16,    0,  108,    2, 0x08 /* Private */,
      17,    1,  109,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onNewInstance(); break;
        case 1: _t->onInsertHead(); break;
        case 2: _t->onInsertTail(); break;
        case 3: _t->onDeleteAt(); break;
        case 4: _t->onNewStackInstance(); break;
        case 5: _t->onPush(); break;
        case 6: _t->onPop(); break;
        case 7: _t->onTraverseLinkedList(); break;
        case 8: _t->onNewCircularQueueInstance(); break;
        case 9: _t->onNewCustomCapacityQueueInstance(); break;
        case 10: _t->onEnqueue(); break;
        case 11: _t->onDequeue(); break;
        case 12: _t->onScreenshot(); break;
        case 13: _t->onSaveToFile(); break;
        case 14: _t->onLoadFromFile(); break;
        case 15: _t->onTabCloseRequested((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
