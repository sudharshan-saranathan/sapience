/****************************************************************************
** Meta object code from reading C++ file 'qBezier.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../include/link/qBezier.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qBezier.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_qBezier_t {
    uint offsetsAndSizes[10];
    char stringdata0[8];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[26];
    char stringdata4[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_qBezier_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_qBezier_t qt_meta_stringdata_qBezier = {
    {
        QT_MOC_LITERAL(0, 7),  // "qBezier"
        QT_MOC_LITERAL(8, 15),  // "hoverEnterEvent"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 25),  // "QGraphicsSceneHoverEvent*"
        QT_MOC_LITERAL(51, 15)   // "hoverLeaveEvent"
    },
    "qBezier",
    "hoverEnterEvent",
    "",
    "QGraphicsSceneHoverEvent*",
    "hoverLeaveEvent"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_qBezier[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x09,    1 /* Protected */,
       4,    1,   29,    2, 0x09,    3 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject qBezier::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_qBezier.offsetsAndSizes,
    qt_meta_data_qBezier,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_qBezier_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<qBezier, std::true_type>,
        // method 'hoverEnterEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QGraphicsSceneHoverEvent *, std::false_type>,
        // method 'hoverLeaveEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QGraphicsSceneHoverEvent *, std::false_type>
    >,
    nullptr
} };

void qBezier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<qBezier *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->hoverEnterEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneHoverEvent*>>(_a[1]))); break;
        case 1: _t->hoverLeaveEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneHoverEvent*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *qBezier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qBezier::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qBezier.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QPathG"))
        return static_cast< QPathG*>(this);
    if (!strcmp(_clname, "qDesign"))
        return static_cast< qDesign*>(this);
    return QObject::qt_metacast(_clname);
}

int qBezier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
