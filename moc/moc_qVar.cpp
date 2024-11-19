/****************************************************************************
** Meta object code from reading C++ file 'qVar.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../include/node/qVar.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qVar.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_qLabel_t {
    uint offsetsAndSizes[6];
    char stringdata0[7];
    char stringdata1[13];
    char stringdata2[1];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_qLabel_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_qLabel_t qt_meta_stringdata_qLabel = {
    {
        QT_MOC_LITERAL(0, 6),  // "qLabel"
        QT_MOC_LITERAL(7, 12),  // "label_update"
        QT_MOC_LITERAL(20, 0)   // ""
    },
    "qLabel",
    "label_update",
    ""
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_qLabel[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   20,    2, 0x06,    1 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject qLabel::staticMetaObject = { {
    QMetaObject::SuperData::link<QItemT::staticMetaObject>(),
    qt_meta_stringdata_qLabel.offsetsAndSizes,
    qt_meta_data_qLabel,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_qLabel_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<qLabel, std::true_type>,
        // method 'label_update'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void qLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<qLabel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->label_update((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (qLabel::*)(const QString & );
            if (_t _q_method = &qLabel::label_update; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *qLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qLabel.stringdata0))
        return static_cast<void*>(this);
    return QItemT::qt_metacast(_clname);
}

int qLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemT::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void qLabel::label_update(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
namespace {
struct qt_meta_stringdata_qVar_t {
    uint offsetsAndSizes[38];
    char stringdata0[5];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[6];
    char stringdata5[12];
    char stringdata6[12];
    char stringdata7[11];
    char stringdata8[11];
    char stringdata9[12];
    char stringdata10[11];
    char stringdata11[8];
    char stringdata12[16];
    char stringdata13[26];
    char stringdata14[16];
    char stringdata15[16];
    char stringdata16[26];
    char stringdata17[18];
    char stringdata18[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_qVar_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_qVar_t qt_meta_stringdata_qVar = {
    {
        QT_MOC_LITERAL(0, 4),  // "qVar"
        QT_MOC_LITERAL(5, 11),  // "enroll_sock"
        QT_MOC_LITERAL(17, 0),  // ""
        QT_MOC_LITERAL(18, 6),  // "qNode*"
        QT_MOC_LITERAL(25, 5),  // "qVar*"
        QT_MOC_LITERAL(31, 11),  // "create_link"
        QT_MOC_LITERAL(43, 11),  // "adjust_link"
        QT_MOC_LITERAL(55, 10),  // "update_var"
        QT_MOC_LITERAL(66, 10),  // "delete_var"
        QT_MOC_LITERAL(77, 11),  // "replace_var"
        QT_MOC_LITERAL(89, 10),  // "itemChange"
        QT_MOC_LITERAL(100, 7),  // "QChange"
        QT_MOC_LITERAL(108, 15),  // "hoverEnterEvent"
        QT_MOC_LITERAL(124, 25),  // "QGraphicsSceneHoverEvent*"
        QT_MOC_LITERAL(150, 15),  // "hoverLeaveEvent"
        QT_MOC_LITERAL(166, 15),  // "mousePressEvent"
        QT_MOC_LITERAL(182, 25),  // "QGraphicsSceneMouseEvent*"
        QT_MOC_LITERAL(208, 17),  // "mouseReleaseEvent"
        QT_MOC_LITERAL(226, 15)   // "on_label_update"
    },
    "qVar",
    "enroll_sock",
    "",
    "qNode*",
    "qVar*",
    "create_link",
    "adjust_link",
    "update_var",
    "delete_var",
    "replace_var",
    "itemChange",
    "QChange",
    "hoverEnterEvent",
    "QGraphicsSceneHoverEvent*",
    "hoverLeaveEvent",
    "mousePressEvent",
    "QGraphicsSceneMouseEvent*",
    "mouseReleaseEvent",
    "on_label_update"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_qVar[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   86,    2, 0x06,    1 /* Public */,
       5,    2,   91,    2, 0x06,    4 /* Public */,
       6,    2,   96,    2, 0x06,    7 /* Public */,
       7,    2,  101,    2, 0x06,   10 /* Public */,
       8,    2,  106,    2, 0x06,   13 /* Public */,
       9,    2,  111,    2, 0x06,   16 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    2,  116,    2, 0x09,   19 /* Protected */,
      12,    1,  121,    2, 0x09,   22 /* Protected */,
      14,    1,  124,    2, 0x09,   24 /* Protected */,
      15,    1,  127,    2, 0x09,   26 /* Protected */,
      17,    1,  130,    2, 0x09,   28 /* Protected */,
      18,    1,  133,    2, 0x09,   30 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    2,    2,

 // slots: parameters
    QMetaType::QVariant, 0x80000000 | 11, QMetaType::QVariant,    2,    2,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject qVar::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_qVar.offsetsAndSizes,
    qt_meta_data_qVar,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_qVar_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<qVar, std::true_type>,
        // method 'enroll_sock'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qNode *, std::false_type>,
        QtPrivate::TypeAndForceComplete<qVar *, std::false_type>,
        // method 'create_link'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qNode *, std::false_type>,
        QtPrivate::TypeAndForceComplete<qVar *, std::false_type>,
        // method 'adjust_link'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qNode *, std::false_type>,
        QtPrivate::TypeAndForceComplete<qVar *, std::false_type>,
        // method 'update_var'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qNode *, std::false_type>,
        QtPrivate::TypeAndForceComplete<qVar *, std::false_type>,
        // method 'delete_var'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qNode *, std::false_type>,
        QtPrivate::TypeAndForceComplete<qVar *, std::false_type>,
        // method 'replace_var'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<qVar *, std::false_type>,
        // method 'itemChange'
        QtPrivate::TypeAndForceComplete<QVariant, std::false_type>,
        QtPrivate::TypeAndForceComplete<QChange, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVariant &, std::false_type>,
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
        // method 'on_label_update'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void qVar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<qVar *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->enroll_sock((*reinterpret_cast< std::add_pointer_t<qNode*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qVar*>>(_a[2]))); break;
        case 1: _t->create_link((*reinterpret_cast< std::add_pointer_t<qNode*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qVar*>>(_a[2]))); break;
        case 2: _t->adjust_link((*reinterpret_cast< std::add_pointer_t<qNode*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qVar*>>(_a[2]))); break;
        case 3: _t->update_var((*reinterpret_cast< std::add_pointer_t<qNode*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qVar*>>(_a[2]))); break;
        case 4: _t->delete_var((*reinterpret_cast< std::add_pointer_t<qNode*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qVar*>>(_a[2]))); break;
        case 5: _t->replace_var((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qVar*>>(_a[2]))); break;
        case 6: { QVariant _r = _t->itemChange((*reinterpret_cast< std::add_pointer_t<QChange>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->hoverEnterEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneHoverEvent*>>(_a[1]))); break;
        case 8: _t->hoverLeaveEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneHoverEvent*>>(_a[1]))); break;
        case 9: _t->mousePressEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneMouseEvent*>>(_a[1]))); break;
        case 10: _t->mouseReleaseEvent((*reinterpret_cast< std::add_pointer_t<QGraphicsSceneMouseEvent*>>(_a[1]))); break;
        case 11: _t->on_label_update((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< qVar* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< qVar* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< qVar* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< qVar* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< qVar* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< qVar* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (qVar::*)(qNode * , qVar * );
            if (_t _q_method = &qVar::enroll_sock; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (qVar::*)(qNode * , qVar * );
            if (_t _q_method = &qVar::create_link; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (qVar::*)(qNode * , qVar * );
            if (_t _q_method = &qVar::adjust_link; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (qVar::*)(qNode * , qVar * );
            if (_t _q_method = &qVar::update_var; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (qVar::*)(qNode * , qVar * );
            if (_t _q_method = &qVar::delete_var; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (qVar::*)(QString , qVar * );
            if (_t _q_method = &qVar::replace_var; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject *qVar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qVar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qVar.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QItemE"))
        return static_cast< QItemE*>(this);
    if (!strcmp(_clname, "qDesign"))
        return static_cast< qDesign*>(this);
    return QObject::qt_metacast(_clname);
}

int qVar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void qVar::enroll_sock(qNode * _t1, qVar * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void qVar::create_link(qNode * _t1, qVar * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void qVar::adjust_link(qNode * _t1, qVar * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void qVar::update_var(qNode * _t1, qVar * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void qVar::delete_var(qNode * _t1, qVar * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void qVar::replace_var(QString _t1, qVar * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
