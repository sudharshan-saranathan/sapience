/****************************************************************************
** Meta object code from reading C++ file 'viewer.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../include/view/qView.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewer.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_qView_t {
    uint offsetsAndSizes[32];
    char stringdata0[6];
    char stringdata1[7];
    char stringdata2[22];
    char stringdata3[12];
    char stringdata4[1];
    char stringdata5[5];
    char stringdata6[5];
    char stringdata7[6];
    char stringdata8[14];
    char stringdata9[15];
    char stringdata10[7];
    char stringdata11[11];
    char stringdata12[13];
    char stringdata13[14];
    char stringdata14[11];
    char stringdata15[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_qView_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_qView_t qt_meta_stringdata_qView = {
    {
        QT_MOC_LITERAL(0, 5),  // "qView"
        QT_MOC_LITERAL(6, 6),  // "Author"
        QT_MOC_LITERAL(13, 21),  // "Sudharshan Saranathan"
        QT_MOC_LITERAL(35, 11),  // "initialized"
        QT_MOC_LITERAL(47, 0),  // ""
        QT_MOC_LITERAL(48, 4),  // "open"
        QT_MOC_LITERAL(53, 4),  // "save"
        QT_MOC_LITERAL(58, 5),  // "clear"
        QT_MOC_LITERAL(64, 13),  // "on_pane_setup"
        QT_MOC_LITERAL(78, 14),  // "on_node_select"
        QT_MOC_LITERAL(93, 6),  // "qNode*"
        QT_MOC_LITERAL(100, 10),  // "wheelEvent"
        QT_MOC_LITERAL(111, 12),  // "QWheelEvent*"
        QT_MOC_LITERAL(124, 13),  // "keyPressEvent"
        QT_MOC_LITERAL(138, 10),  // "QKeyEvent*"
        QT_MOC_LITERAL(149, 15)   // "keyReleaseEvent"
    },
    "qView",
    "Author",
    "Sudharshan Saranathan",
    "initialized",
    "",
    "open",
    "save",
    "clear",
    "on_pane_setup",
    "on_node_select",
    "qNode*",
    "wheelEvent",
    "QWheelEvent*",
    "keyPressEvent",
    "QKeyEvent*",
    "keyReleaseEvent"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_qView[] = {

 // content:
      10,       // revision
       0,       // classname
       1,   14, // classinfo
       9,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   70,    4, 0x06,    1 /* Public */,
       5,    0,   71,    4, 0x06,    2 /* Public */,
       6,    0,   72,    4, 0x06,    3 /* Public */,
       7,    0,   73,    4, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    0,   74,    4, 0x0a,    5 /* Public */,
       9,    2,   75,    4, 0x0a,    6 /* Public */,
      11,    1,   80,    4, 0x09,    9 /* Protected */,
      13,    1,   83,    4, 0x09,   11 /* Protected */,
      15,    1,   86,    4, 0x09,   13 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 10,    4,    4,
    QMetaType::Void, 0x80000000 | 12,    4,
    QMetaType::Void, 0x80000000 | 14,    4,
    QMetaType::Void, 0x80000000 | 14,    4,

       0        // eod
};

Q_CONSTINIT const QMetaObject qView::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_meta_stringdata_qView.offsetsAndSizes,
    qt_meta_data_qView,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_qView_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<qView, std::true_type>,
        // method 'initialized'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'open'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'save'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clear'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pane_setup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_node_select'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<qNode *, std::false_type>,
        // method 'wheelEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWheelEvent *, std::false_type>,
        // method 'keyPressEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QKeyEvent *, std::false_type>,
        // method 'keyReleaseEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QKeyEvent *, std::false_type>
    >,
    nullptr
} };

void qView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<qView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->initialized(); break;
        case 1: _t->open(); break;
        case 2: _t->save(); break;
        case 3: _t->clear(); break;
        case 4: _t->on_pane_setup(); break;
        case 5: _t->on_node_select((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qNode*>>(_a[2]))); break;
        case 6: _t->wheelEvent((*reinterpret_cast< std::add_pointer_t<QWheelEvent*>>(_a[1]))); break;
        case 7: _t->keyPressEvent((*reinterpret_cast< std::add_pointer_t<QKeyEvent*>>(_a[1]))); break;
        case 8: _t->keyReleaseEvent((*reinterpret_cast< std::add_pointer_t<QKeyEvent*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< qNode* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (qView::*)();
            if (_t _q_method = &qView::initialized; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (qView::*)();
            if (_t _q_method = &qView::open; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (qView::*)();
            if (_t _q_method = &qView::save; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (qView::*)();
            if (_t _q_method = &qView::clear; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *qView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qView.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int qView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void qView::initialized()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void qView::open()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void qView::save()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void qView::clear()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
