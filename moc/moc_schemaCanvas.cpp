/****************************************************************************
** Meta object code from reading C++ file 'schemaCanvas.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/schematic/schemaCanvas.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'schemaCanvas.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSschemaCanvasENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSschemaCanvasENDCLASS = QtMocHelpers::stringData(
    "schemaCanvas",
    "Author",
    "Sudharshan Saranathan",
    "initialized",
    "",
    "quitProgram",
    "startConnection",
    "nodeCtrl*",
    "nodeVar*",
    "createNode",
    "nodeCtrl",
    "createGroup",
    "QGroup*",
    "QList<QItemG*>",
    "createFolder",
    "deleteNode",
    "deleteSchema",
    "shortcutCopy",
    "shortcutPaste",
    "shortcutDelete",
    "shortcutSelect",
    "mouseMoveEvent",
    "QGraphicsSceneMouseEvent*",
    "event",
    "mousePressEvent",
    "mouseReleaseEvent",
    "contextMenuEvent",
    "QGraphicsSceneContextMenuEvent*",
    "keyPressEvent",
    "QKeyEvent*"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSschemaCanvasENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       1,   14, // classinfo
      18,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,  124,    4, 0x06,    1 /* Public */,
       5,    0,  125,    4, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    2,  126,    4, 0x0a,    3 /* Public */,
       9,    1,  131,    4, 0x0a,    6 /* Public */,
       9,    1,  134,    4, 0x0a,    8 /* Public */,
      11,    1,  137,    4, 0x0a,   10 /* Public */,
      14,    1,  140,    4, 0x0a,   12 /* Public */,
      15,    1,  143,    4, 0x0a,   14 /* Public */,
      16,    0,  146,    4, 0x10a,   16 /* Public | MethodIsConst  */,
      17,    0,  147,    4, 0x0a,   17 /* Public */,
      18,    0,  148,    4, 0x0a,   18 /* Public */,
      19,    0,  149,    4, 0x0a,   19 /* Public */,
      20,    0,  150,    4, 0x0a,   20 /* Public */,
      21,    1,  151,    4, 0x09,   21 /* Protected */,
      24,    1,  154,    4, 0x09,   23 /* Protected */,
      25,    1,  157,    4, 0x09,   25 /* Protected */,
      26,    1,  160,    4, 0x09,   27 /* Protected */,
      28,    1,  163,    4, 0x09,   29 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 8,    4,    4,
    0x80000000 | 7, QMetaType::QPointF,    4,
    0x80000000 | 7, 0x80000000 | 10,    4,
    0x80000000 | 12, 0x80000000 | 13,    4,
    QMetaType::Void, QMetaType::QPointF,    4,
    QMetaType::Void, 0x80000000 | 7,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, 0x80000000 | 27,   23,
    QMetaType::Void, 0x80000000 | 29,   23,

       0        // eod
};

Q_CONSTINIT const QMetaObject schemaCanvas::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsScene::staticMetaObject>(),
    qt_meta_stringdata_CLASSschemaCanvasENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSschemaCanvasENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSschemaCanvasENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<schemaCanvas, std::true_type>,
        // method 'initialized'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'quitProgram'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startConnection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<nodeCtrl *, std::false_type>,
        QtPrivate::TypeAndForceComplete<nodeVar *, std::false_type>,
        // method 'createNode'
        QtPrivate::TypeAndForceComplete<nodeCtrl *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPointF &, std::false_type>,
        // method 'createNode'
        QtPrivate::TypeAndForceComplete<nodeCtrl *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const nodeCtrl &, std::false_type>,
        // method 'createGroup'
        QtPrivate::TypeAndForceComplete<QGroup *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QItemG*> &, std::false_type>,
        // method 'createFolder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPointF &, std::false_type>,
        // method 'deleteNode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<nodeCtrl *, std::false_type>,
        // method 'deleteSchema'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'shortcutCopy'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'shortcutPaste'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'shortcutDelete'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'shortcutSelect'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'mouseMoveEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QGraphicsSceneMouseEvent *, std::false_type>,
        // method 'mousePressEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QGraphicsSceneMouseEvent *, std::false_type>,
        // method 'mouseReleaseEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QGraphicsSceneMouseEvent *, std::false_type>,
        // method 'contextMenuEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QGraphicsSceneContextMenuEvent *, std::false_type>,
        // method 'keyPressEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QKeyEvent *, std::false_type>
    >,
    nullptr
} };

void schemaCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<schemaCanvas *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->initialized(); break;
        case 1: _t->quitProgram(); break;
        case 2: _t->startConnection((*reinterpret_cast< std::add_pointer_t<nodeCtrl*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<nodeVar*>>(_a[2]))); break;
        case 3: { nodeCtrl* _r = _t->createNode((*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[1])));
            if (_a[0]) *reinterpret_cast< nodeCtrl**>(_a[0]) = std::move(_r); }  break;
        case 4: { nodeCtrl* _r = _t->createNode((*reinterpret_cast< std::add_pointer_t<nodeCtrl>>(_a[1])));
            if (_a[0]) *reinterpret_cast< nodeCtrl**>(_a[0]) = std::move(_r); }  break;
        case 5: { QGroup* _r = _t->createGroup((*reinterpret_cast< std::add_pointer_t<QList<QItemG*>>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QGroup**>(_a[0]) = std::move(_r); }  break;
        case 6: _t->createFolder((*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[1]))); break;
        case 7: _t->deleteNode((*reinterpret_cast< std::add_pointer_t<nodeCtrl*>>(_a[1]))); break;
        case 8: _t->deleteSchema(); break;
        case 9: _t->shortcutCopy(); break;
        case 10: _t->shortcutPaste(); break;
        case 11: _t->shortcutDelete(); break;
        case 12: _t->shortcutSelect(); break;
        case 13: _t->mouseMoveEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneMouseEvent*>>(_a[1]))); break;
        case 14: _t->mousePressEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneMouseEvent*>>(_a[1]))); break;
        case 15: _t->mouseReleaseEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneMouseEvent*>>(_a[1]))); break;
        case 16: _t->contextMenuEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneContextMenuEvent*>>(_a[1]))); break;
        case 17: _t->keyPressEvent((*reinterpret_cast< std::add_pointer_t<QKeyEvent*>>(_a[1]))); break;
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
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< nodeVar* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< nodeCtrl* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (schemaCanvas::*)();
            if (_t _q_method = &schemaCanvas::initialized; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (schemaCanvas::*)();
            if (_t _q_method = &schemaCanvas::quitProgram; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *schemaCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *schemaCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSschemaCanvasENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int schemaCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void schemaCanvas::initialized()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void schemaCanvas::quitProgram()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
