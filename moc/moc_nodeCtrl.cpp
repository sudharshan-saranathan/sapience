/****************************************************************************
** Meta object code from reading C++ file 'nodeCtrl.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/node/nodeCtrl.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nodeCtrl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.0. It"
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
struct qt_meta_stringdata_CLASSnodeCtrlENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSnodeCtrlENDCLASS = QtMocHelpers::stringData(
    "nodeCtrl",
    "Author",
    "Sudharshan Saranathan",
    "initialized",
    "",
    "nodeShifted",
    "nodeDeleted",
    "nodeCtrl*",
    "linkVariable",
    "nodeVar*",
    "itemChange",
    "QVariant",
    "GraphicsItemChange",
    "change",
    "value",
    "paint",
    "QPainter*",
    "const QStOGI*",
    "QWidget*",
    "hoverMoveEvent",
    "QGraphicsSceneHoverEvent*",
    "hoverEnterEvent",
    "hoverLeaveEvent",
    "mousePressEvent",
    "QGraphicsSceneMouseEvent*",
    "event",
    "mouseReleaseEvent",
    "contextMenuEvent",
    "QGraphicsSceneContextMenuEvent*"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSnodeCtrlENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       1,   14, // classinfo
      12,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   88,    4, 0x06,    1 /* Public */,
       5,    0,   89,    4, 0x06,    2 /* Public */,
       6,    1,   90,    4, 0x06,    3 /* Public */,
       8,    2,   93,    4, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    2,   98,    4, 0x09,    8 /* Protected */,
      15,    3,  103,    4, 0x09,   11 /* Protected */,
      19,    1,  110,    4, 0x09,   15 /* Protected */,
      21,    1,  113,    4, 0x09,   17 /* Protected */,
      22,    1,  116,    4, 0x09,   19 /* Protected */,
      23,    1,  119,    4, 0x09,   21 /* Protected */,
      26,    1,  122,    4, 0x09,   23 /* Protected */,
      27,    1,  125,    4, 0x09,   25 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    4,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 9,    4,    4,

 // slots: parameters
    0x80000000 | 11, 0x80000000 | 12, 0x80000000 | 11,   13,   14,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 17, 0x80000000 | 18,    4,    4,    4,
    QMetaType::Void, 0x80000000 | 20,    4,
    QMetaType::Void, 0x80000000 | 20,    4,
    QMetaType::Void, 0x80000000 | 20,    4,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void, 0x80000000 | 28,   25,

       0        // eod
};

Q_CONSTINIT const QMetaObject nodeCtrl::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSnodeCtrlENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSnodeCtrlENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSnodeCtrlENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<nodeCtrl, std::true_type>,
        // method 'initialized'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'nodeShifted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'nodeDeleted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<nodeCtrl *, std::false_type>,
        // method 'linkVariable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<nodeCtrl *, std::false_type>,
        QtPrivate::TypeAndForceComplete<nodeVar *, std::false_type>,
        // method 'itemChange'
        QtPrivate::TypeAndForceComplete<QVariant, std::false_type>,
        QtPrivate::TypeAndForceComplete<GraphicsItemChange, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVariant &, std::false_type>,
        // method 'paint'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPainter *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QStOGI *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>,
        // method 'hoverMoveEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QGraphicsSceneHoverEvent *, std::false_type>,
        // method 'hoverEnterEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QGraphicsSceneHoverEvent *, std::false_type>,
        // method 'hoverLeaveEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QGraphicsSceneHoverEvent *, std::false_type>,
        // method 'mousePressEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QGraphicsSceneMouseEvent *, std::false_type>,
        // method 'mouseReleaseEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QGraphicsSceneMouseEvent *, std::false_type>,
        // method 'contextMenuEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QGraphicsSceneContextMenuEvent *, std::false_type>
    >,
    nullptr
} };

void nodeCtrl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<nodeCtrl *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->initialized(); break;
        case 1: _t->nodeShifted(); break;
        case 2: _t->nodeDeleted((*reinterpret_cast< std::add_pointer_t<nodeCtrl*>>(_a[1]))); break;
        case 3: _t->linkVariable((*reinterpret_cast< std::add_pointer_t<nodeCtrl*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<nodeVar*>>(_a[2]))); break;
        case 4: { QVariant _r = _t->itemChange((*reinterpret_cast< std::add_pointer_t<GraphicsItemChange>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->paint((*reinterpret_cast< std::add_pointer_t<QPainter*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<const QStOGI*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[3]))); break;
        case 6: _t->hoverMoveEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneHoverEvent*>>(_a[1]))); break;
        case 7: _t->hoverEnterEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneHoverEvent*>>(_a[1]))); break;
        case 8: _t->hoverLeaveEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneHoverEvent*>>(_a[1]))); break;
        case 9: _t->mousePressEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneMouseEvent*>>(_a[1]))); break;
        case 10: _t->mouseReleaseEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneMouseEvent*>>(_a[1]))); break;
        case 11: _t->contextMenuEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneContextMenuEvent*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< nodeCtrl* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< nodeCtrl* >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< nodeVar* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 2:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (nodeCtrl::*)();
            if (_t _q_method = &nodeCtrl::initialized; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (nodeCtrl::*)();
            if (_t _q_method = &nodeCtrl::nodeShifted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (nodeCtrl::*)(nodeCtrl * );
            if (_t _q_method = &nodeCtrl::nodeDeleted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (nodeCtrl::*)(nodeCtrl * , nodeVar * );
            if (_t _q_method = &nodeCtrl::linkVariable; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *nodeCtrl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *nodeCtrl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSnodeCtrlENDCLASS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsRectItem"))
        return static_cast< QGraphicsRectItem*>(this);
    return QObject::qt_metacast(_clname);
}

int nodeCtrl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void nodeCtrl::initialized()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void nodeCtrl::nodeShifted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void nodeCtrl::nodeDeleted(nodeCtrl * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void nodeCtrl::linkVariable(nodeCtrl * _t1, nodeVar * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
