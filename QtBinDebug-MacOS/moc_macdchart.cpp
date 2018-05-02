/****************************************************************************
** Meta object code from reading C++ file 'macdchart.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../macdchart.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'macdchart.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MACDChart_t {
    QByteArrayData data[12];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MACDChart_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MACDChart_t qt_meta_stringdata_MACDChart = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MACDChart"
QT_MOC_LITERAL(1, 10, 9), // "addSeries"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 12), // "QLineSeries*"
QT_MOC_LITERAL(4, 34, 7), // "addAxis"
QT_MOC_LITERAL(5, 42, 14), // "QAbstractAxis*"
QT_MOC_LITERAL(6, 57, 13), // "Qt::Alignment"
QT_MOC_LITERAL(7, 71, 11), // "returnChart"
QT_MOC_LITERAL(8, 83, 7), // "QChart*"
QT_MOC_LITERAL(9, 91, 14), // "connectMarkers"
QT_MOC_LITERAL(10, 106, 17), // "disconnectMarkers"
QT_MOC_LITERAL(11, 124, 19) // "handleMarkerClicked"

    },
    "MACDChart\0addSeries\0\0QLineSeries*\0"
    "addAxis\0QAbstractAxis*\0Qt::Alignment\0"
    "returnChart\0QChart*\0connectMarkers\0"
    "disconnectMarkers\0handleMarkerClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MACDChart[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       4,    2,   47,    2, 0x0a /* Public */,
       7,    0,   52,    2, 0x0a /* Public */,
       9,    0,   53,    2, 0x0a /* Public */,
      10,    0,   54,    2, 0x0a /* Public */,
      11,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 6,    2,    2,
    0x80000000 | 8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MACDChart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MACDChart *_t = static_cast<MACDChart *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addSeries((*reinterpret_cast< QLineSeries*(*)>(_a[1]))); break;
        case 1: _t->addAxis((*reinterpret_cast< QAbstractAxis*(*)>(_a[1])),(*reinterpret_cast< Qt::Alignment(*)>(_a[2]))); break;
        case 2: { QChart* _r = _t->returnChart();
            if (_a[0]) *reinterpret_cast< QChart**>(_a[0]) = _r; }  break;
        case 3: _t->connectMarkers(); break;
        case 4: _t->disconnectMarkers(); break;
        case 5: _t->handleMarkerClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLineSeries* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractAxis* >(); break;
            }
            break;
        }
    }
}

const QMetaObject MACDChart::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MACDChart.data,
      qt_meta_data_MACDChart,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MACDChart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MACDChart::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MACDChart.stringdata0))
        return static_cast<void*>(const_cast< MACDChart*>(this));
    return QWidget::qt_metacast(_clname);
}

int MACDChart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
