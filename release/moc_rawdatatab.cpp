/****************************************************************************
** Meta object code from reading C++ file 'rawdatatab.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../rawdatatab.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rawdatatab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSRawDataTabENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSRawDataTabENDCLASS = QtMocHelpers::stringData(
    "RawDataTab",
    "eventPlotDataPointSelected",
    "",
    "eventId",
    "time",
    "dataIndex",
    "currentEventIdChanged",
    "eventIdChanged",
    "setVisibility",
    "graphId",
    "isVisible",
    "overviewPlotClicked",
    "QCPAbstractPlottable*",
    "plottable",
    "eventPlotClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSRawDataTabENDCLASS_t {
    uint offsetsAndSizes[30];
    char stringdata0[11];
    char stringdata1[27];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[5];
    char stringdata5[10];
    char stringdata6[22];
    char stringdata7[15];
    char stringdata8[14];
    char stringdata9[8];
    char stringdata10[10];
    char stringdata11[20];
    char stringdata12[22];
    char stringdata13[10];
    char stringdata14[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSRawDataTabENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSRawDataTabENDCLASS_t qt_meta_stringdata_CLASSRawDataTabENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "RawDataTab"
        QT_MOC_LITERAL(11, 26),  // "eventPlotDataPointSelected"
        QT_MOC_LITERAL(38, 0),  // ""
        QT_MOC_LITERAL(39, 7),  // "eventId"
        QT_MOC_LITERAL(47, 4),  // "time"
        QT_MOC_LITERAL(52, 9),  // "dataIndex"
        QT_MOC_LITERAL(62, 21),  // "currentEventIdChanged"
        QT_MOC_LITERAL(84, 14),  // "eventIdChanged"
        QT_MOC_LITERAL(99, 13),  // "setVisibility"
        QT_MOC_LITERAL(113, 7),  // "graphId"
        QT_MOC_LITERAL(121, 9),  // "isVisible"
        QT_MOC_LITERAL(131, 19),  // "overviewPlotClicked"
        QT_MOC_LITERAL(151, 21),  // "QCPAbstractPlottable*"
        QT_MOC_LITERAL(173, 9),  // "plottable"
        QT_MOC_LITERAL(183, 16)   // "eventPlotClicked"
    },
    "RawDataTab",
    "eventPlotDataPointSelected",
    "",
    "eventId",
    "time",
    "dataIndex",
    "currentEventIdChanged",
    "eventIdChanged",
    "setVisibility",
    "graphId",
    "isVisible",
    "overviewPlotClicked",
    "QCPAbstractPlottable*",
    "plottable",
    "eventPlotClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSRawDataTabENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,   50,    2, 0x06,    1 /* Public */,
       6,    1,   57,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    1,   60,    2, 0x0a,    7 /* Public */,
       8,    2,   63,    2, 0x0a,    9 /* Public */,
      11,    2,   68,    2, 0x08,   12 /* Private */,
      14,    2,   73,    2, 0x08,   15 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Double, QMetaType::Int,    3,    4,    5,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    9,   10,
    QMetaType::Void, 0x80000000 | 12, QMetaType::Int,   13,    5,
    QMetaType::Void, 0x80000000 | 12, QMetaType::Int,   13,    5,

       0        // eod
};

Q_CONSTINIT const QMetaObject RawDataTab::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSRawDataTabENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSRawDataTabENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSRawDataTabENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<RawDataTab, std::true_type>,
        // method 'eventPlotDataPointSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'currentEventIdChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'eventIdChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setVisibility'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'overviewPlotClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAbstractPlottable *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'eventPlotClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAbstractPlottable *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void RawDataTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RawDataTab *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->eventPlotDataPointSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 1: _t->currentEventIdChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->eventIdChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->setVisibility((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 4: _t->overviewPlotClicked((*reinterpret_cast< std::add_pointer_t<QCPAbstractPlottable*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 5: _t->eventPlotClicked((*reinterpret_cast< std::add_pointer_t<QCPAbstractPlottable*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAbstractPlottable* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAbstractPlottable* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RawDataTab::*)(int , double , int );
            if (_t _q_method = &RawDataTab::eventPlotDataPointSelected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RawDataTab::*)(int );
            if (_t _q_method = &RawDataTab::currentEventIdChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *RawDataTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RawDataTab::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSRawDataTabENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RawDataTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void RawDataTab::eventPlotDataPointSelected(int _t1, double _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RawDataTab::currentEventIdChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
