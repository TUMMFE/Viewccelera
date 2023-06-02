/****************************************************************************
** Meta object code from reading C++ file 'analyser.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../analyser.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'analyser.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSAnalyserENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSAnalyserENDCLASS = QtMocHelpers::stringData(
    "Analyser",
    "analysisFinishied",
    "",
    "AnalysisDataFrame",
    "dataFrame",
    "startAnalysis",
    "saveEventData",
    "filename",
    "saveAnalysedData",
    "QList<AnalysisDataFrame>",
    "dataFrames",
    "compare",
    "i",
    "j"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSAnalyserENDCLASS_t {
    uint offsetsAndSizes[28];
    char stringdata0[9];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[18];
    char stringdata4[10];
    char stringdata5[14];
    char stringdata6[14];
    char stringdata7[9];
    char stringdata8[17];
    char stringdata9[25];
    char stringdata10[11];
    char stringdata11[8];
    char stringdata12[2];
    char stringdata13[2];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSAnalyserENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSAnalyserENDCLASS_t qt_meta_stringdata_CLASSAnalyserENDCLASS = {
    {
        QT_MOC_LITERAL(0, 8),  // "Analyser"
        QT_MOC_LITERAL(9, 17),  // "analysisFinishied"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 17),  // "AnalysisDataFrame"
        QT_MOC_LITERAL(46, 9),  // "dataFrame"
        QT_MOC_LITERAL(56, 13),  // "startAnalysis"
        QT_MOC_LITERAL(70, 13),  // "saveEventData"
        QT_MOC_LITERAL(84, 8),  // "filename"
        QT_MOC_LITERAL(93, 16),  // "saveAnalysedData"
        QT_MOC_LITERAL(110, 24),  // "QList<AnalysisDataFrame>"
        QT_MOC_LITERAL(135, 10),  // "dataFrames"
        QT_MOC_LITERAL(146, 7),  // "compare"
        QT_MOC_LITERAL(154, 1),  // "i"
        QT_MOC_LITERAL(156, 1)   // "j"
    },
    "Analyser",
    "analysisFinishied",
    "",
    "AnalysisDataFrame",
    "dataFrame",
    "startAnalysis",
    "saveEventData",
    "filename",
    "saveAnalysedData",
    "QList<AnalysisDataFrame>",
    "dataFrames",
    "compare",
    "i",
    "j"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSAnalyserENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   47,    2, 0x0a,    3 /* Public */,
       6,    2,   50,    2, 0x0a,    5 /* Public */,
       8,    2,   55,    2, 0x0a,    8 /* Public */,
      11,    2,   60,    2, 0x0a,   11 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    7,
    QMetaType::Void, 0x80000000 | 9, QMetaType::QString,   10,    7,
    QMetaType::Bool, 0x80000000 | 3, 0x80000000 | 3,   12,   13,

       0        // eod
};

Q_CONSTINIT const QMetaObject Analyser::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSAnalyserENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSAnalyserENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSAnalyserENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Analyser, std::true_type>,
        // method 'analysisFinishied'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<AnalysisDataFrame, std::false_type>,
        // method 'startAnalysis'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<AnalysisDataFrame, std::false_type>,
        // method 'saveEventData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<AnalysisDataFrame, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'saveAnalysedData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QList<AnalysisDataFrame>, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'compare'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const AnalysisDataFrame &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const AnalysisDataFrame &, std::false_type>
    >,
    nullptr
} };

void Analyser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Analyser *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->analysisFinishied((*reinterpret_cast< std::add_pointer_t<AnalysisDataFrame>>(_a[1]))); break;
        case 1: _t->startAnalysis((*reinterpret_cast< std::add_pointer_t<AnalysisDataFrame>>(_a[1]))); break;
        case 2: _t->saveEventData((*reinterpret_cast< std::add_pointer_t<AnalysisDataFrame>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->saveAnalysedData((*reinterpret_cast< std::add_pointer_t<QList<AnalysisDataFrame>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: { bool _r = _t->compare((*reinterpret_cast< std::add_pointer_t<AnalysisDataFrame>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<AnalysisDataFrame>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Analyser::*)(AnalysisDataFrame );
            if (_t _q_method = &Analyser::analysisFinishied; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *Analyser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Analyser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSAnalyserENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Analyser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Analyser::analysisFinishied(AnalysisDataFrame _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
