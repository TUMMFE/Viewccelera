/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
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
#error "The header file 'mainwindow.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "analyzeRequest",
    "",
    "AnalysisDataFrame",
    "dataFrame",
    "eventIdChanged",
    "eventId",
    "visibilityRawDataChanged",
    "graphId",
    "isVisible",
    "visibilityProcessedDataChanged",
    "dataFrameChanged",
    "analyzeFinished",
    "dockWidgetClosed",
    "analyzedFramesListDoubleClick",
    "QListWidgetItem*",
    "eventPlotDataPointSelected",
    "time",
    "dataIndex",
    "currentEventIdChanged"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[40];
    char stringdata0[11];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[18];
    char stringdata4[10];
    char stringdata5[15];
    char stringdata6[8];
    char stringdata7[25];
    char stringdata8[8];
    char stringdata9[10];
    char stringdata10[31];
    char stringdata11[17];
    char stringdata12[16];
    char stringdata13[17];
    char stringdata14[30];
    char stringdata15[17];
    char stringdata16[27];
    char stringdata17[5];
    char stringdata18[10];
    char stringdata19[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 14),  // "analyzeRequest"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 17),  // "AnalysisDataFrame"
        QT_MOC_LITERAL(45, 9),  // "dataFrame"
        QT_MOC_LITERAL(55, 14),  // "eventIdChanged"
        QT_MOC_LITERAL(70, 7),  // "eventId"
        QT_MOC_LITERAL(78, 24),  // "visibilityRawDataChanged"
        QT_MOC_LITERAL(103, 7),  // "graphId"
        QT_MOC_LITERAL(111, 9),  // "isVisible"
        QT_MOC_LITERAL(121, 30),  // "visibilityProcessedDataChanged"
        QT_MOC_LITERAL(152, 16),  // "dataFrameChanged"
        QT_MOC_LITERAL(169, 15),  // "analyzeFinished"
        QT_MOC_LITERAL(185, 16),  // "dockWidgetClosed"
        QT_MOC_LITERAL(202, 29),  // "analyzedFramesListDoubleClick"
        QT_MOC_LITERAL(232, 16),  // "QListWidgetItem*"
        QT_MOC_LITERAL(249, 26),  // "eventPlotDataPointSelected"
        QT_MOC_LITERAL(276, 4),  // "time"
        QT_MOC_LITERAL(281, 9),  // "dataIndex"
        QT_MOC_LITERAL(291, 21)   // "currentEventIdChanged"
    },
    "MainWindow",
    "analyzeRequest",
    "",
    "AnalysisDataFrame",
    "dataFrame",
    "eventIdChanged",
    "eventId",
    "visibilityRawDataChanged",
    "graphId",
    "isVisible",
    "visibilityProcessedDataChanged",
    "dataFrameChanged",
    "analyzeFinished",
    "dockWidgetClosed",
    "analyzedFramesListDoubleClick",
    "QListWidgetItem*",
    "eventPlotDataPointSelected",
    "time",
    "dataIndex",
    "currentEventIdChanged"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   74,    2, 0x06,    1 /* Public */,
       5,    1,   77,    2, 0x06,    3 /* Public */,
       7,    2,   80,    2, 0x06,    5 /* Public */,
      10,    2,   85,    2, 0x06,    8 /* Public */,
      11,    1,   90,    2, 0x06,   11 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      12,    1,   93,    2, 0x0a,   13 /* Public */,
      13,    1,   96,    2, 0x08,   15 /* Private */,
      14,    1,   99,    2, 0x08,   17 /* Private */,
      16,    3,  102,    2, 0x08,   19 /* Private */,
      19,    1,  109,    2, 0x08,   23 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    8,    9,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Double, QMetaType::Int,    6,   17,   18,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'analyzeRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<AnalysisDataFrame, std::false_type>,
        // method 'eventIdChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'visibilityRawDataChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'visibilityProcessedDataChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'dataFrameChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<AnalysisDataFrame, std::false_type>,
        // method 'analyzeFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<AnalysisDataFrame, std::false_type>,
        // method 'dockWidgetClosed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'analyzedFramesListDoubleClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'eventPlotDataPointSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'currentEventIdChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->analyzeRequest((*reinterpret_cast< std::add_pointer_t<AnalysisDataFrame>>(_a[1]))); break;
        case 1: _t->eventIdChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->visibilityRawDataChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 3: _t->visibilityProcessedDataChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 4: _t->dataFrameChanged((*reinterpret_cast< std::add_pointer_t<AnalysisDataFrame>>(_a[1]))); break;
        case 5: _t->analyzeFinished((*reinterpret_cast< std::add_pointer_t<AnalysisDataFrame>>(_a[1]))); break;
        case 6: _t->dockWidgetClosed((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->analyzedFramesListDoubleClick((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 8: _t->eventPlotDataPointSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 9: _t->currentEventIdChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(AnalysisDataFrame );
            if (_t _q_method = &MainWindow::analyzeRequest; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (_t _q_method = &MainWindow::eventIdChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int , bool );
            if (_t _q_method = &MainWindow::visibilityRawDataChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int , bool );
            if (_t _q_method = &MainWindow::visibilityProcessedDataChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(AnalysisDataFrame );
            if (_t _q_method = &MainWindow::dataFrameChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::analyzeRequest(AnalysisDataFrame _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::eventIdChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::visibilityRawDataChanged(int _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::visibilityProcessedDataChanged(int _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::dataFrameChanged(AnalysisDataFrame _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
