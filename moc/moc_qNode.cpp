/****************************************************************************
** Meta object code from reading C++ file 'nodeControl.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../include/node/qNode.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nodeControl.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_qNode_t {
    uint offsetsAndSizes[38];
    char stringdata0[6];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[11];
    char stringdata5[11];
    char stringdata6[12];
    char stringdata7[12];
    char stringdata8[12];
    char stringdata9[9];
    char stringdata10[10];
    char stringdata11[11];
    char stringdata12[6];
    char stringdata13[11];
    char stringdata14[6];
    char stringdata15[11];
    char stringdata16[14];
    char stringdata17[11];
    char stringdata18[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_qNode_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_qNode_t qt_meta_stringdata_qNode = {
    {
        QT_MOC_LITERAL(0, 5),  // "qNode"
        QT_MOC_LITERAL(6, 10),  // "var_add_ok"
        QT_MOC_LITERAL(17, 0),  // ""
        QT_MOC_LITERAL(18, 6),  // "qNode*"
        QT_MOC_LITERAL(25, 10),  // "var_del_ok"
        QT_MOC_LITERAL(36, 10),  // "var_mod_ok"
        QT_MOC_LITERAL(47, 11),  // "delete_node"
        QT_MOC_LITERAL(59, 11),  // "select_node"
        QT_MOC_LITERAL(71, 11),  // "name_change"
        QT_MOC_LITERAL(83, 8),  // "on_close"
        QT_MOC_LITERAL(92, 9),  // "on_adjust"
        QT_MOC_LITERAL(102, 10),  // "on_add_var"
        QT_MOC_LITERAL(113, 5),  // "qEnum"
        QT_MOC_LITERAL(119, 10),  // "on_del_var"
        QT_MOC_LITERAL(130, 5),  // "qVar*"
        QT_MOC_LITERAL(136, 10),  // "on_mod_var"
        QT_MOC_LITERAL(147, 13),  // "keyPressEvent"
        QT_MOC_LITERAL(161, 10),  // "QKeyEvent*"
        QT_MOC_LITERAL(172, 15)   // "keyReleaseEvent"
    },
    "qNode",
    "var_add_ok",
    "",
    "qNode*",
    "var_del_ok",
    "var_mod_ok",
    "delete_node",
    "select_node",
    "name_change",
    "on_close",
    "on_adjust",
    "on_add_var",
    "qEnum",
    "on_del_var",
    "qVar*",
    "on_mod_var",
    "keyPressEvent",
    "QKeyEvent*",
    "keyReleaseEvent"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_qNode[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  110,    2, 0x06,    1 /* Public */,
       4,    2,  115,    2, 0x06,    4 /* Public */,
       5,    2,  120,    2, 0x06,    7 /* Public */,
       6,    1,  125,    2, 0x06,   10 /* Public */,
       7,    1,  128,    2, 0x06,   12 /* Public */,
       8,    1,  131,    2, 0x06,   14 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,  134,    2, 0x09,   16 /* Protected */,
      10,    0,  135,    2, 0x09,   17 /* Protected */,
      11,    1,  136,    2, 0x09,   18 /* Protected */,
      11,    4,  139,    2, 0x09,   20 /* Protected */,
      13,    2,  148,    2, 0x09,   25 /* Protected */,
      13,    2,  153,    2, 0x09,   28 /* Protected */,
      15,    4,  158,    2, 0x09,   31 /* Protected */,
      15,    2,  167,    2, 0x09,   36 /* Protected */,
      16,    1,  172,    2, 0x09,   39 /* Protected */,
      18,    1,  175,    2, 0x09,   41 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 3,    2,    2,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 3,    2,    2,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 3,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 12, QMetaType::QString, QMetaType::QString, QMetaType::Double,    2,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 12, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 14,    2,    2,
    QMetaType::Void, 0x80000000 | 12, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 14,    2,    2,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void, 0x80000000 | 17,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject qNode::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_qNode.offsetsAndSizes,
    qt_meta_data_qNode,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_qNode_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<qNode, std::true_type>,
        // method 'var_add_ok'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<qNode *, std::false_type>,
        // method 'var_del_ok'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<qNode *, std::false_type>,
        // method 'var_mod_ok'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<qNode *, std::false_type>,
        // method 'delete_node'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qNode *, std::false_type>,
        // method 'select_node'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qNode *, std::false_type>,
        // method 'name_change'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qNode *, std::false_type>,
        // method 'on_close'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_adjust'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_add_var'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qEnum, std::false_type>,
        // method 'on_add_var'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qEnum, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'on_del_var'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qEnum, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_del_var'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qNode *, std::false_type>,
        QtPrivate::TypeAndForceComplete<qVar *, std::false_type>,
        // method 'on_mod_var'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qEnum, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_mod_var'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qNode *, std::false_type>,
        QtPrivate::TypeAndForceComplete<qVar *, std::false_type>,
        // method 'keyPressEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QKeyEvent *, std::false_type>,
        // method 'keyReleaseEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QKeyEvent *, std::false_type>
    >,
    nullptr
} };

void qNode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<qNode *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->var_add_ok((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qNode*>>(_a[2]))); break;
        case 1: _t->var_del_ok((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qNode*>>(_a[2]))); break;
        case 2: _t->var_mod_ok((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qNode*>>(_a[2]))); break;
        case 3: _t->delete_node((*reinterpret_cast< std::add_pointer_t<qNode*>>(_a[1]))); break;
        case 4: _t->select_node((*reinterpret_cast< std::add_pointer_t<qNode*>>(_a[1]))); break;
        case 5: _t->name_change((*reinterpret_cast< std::add_pointer_t<qNode*>>(_a[1]))); break;
        case 6: _t->on_close(); break;
        case 7: _t->on_adjust(); break;
        case 8: _t->on_add_var((*reinterpret_cast< std::add_pointer_t<qEnum>>(_a[1]))); break;
        case 9: _t->on_add_var((*reinterpret_cast< std::add_pointer_t<qEnum>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4]))); break;
        case 10: _t->on_del_var((*reinterpret_cast< std::add_pointer_t<qEnum>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 11: _t->on_del_var((*reinterpret_cast< std::add_pointer_t<qNode*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qVar*>>(_a[2]))); break;
        case 12: _t->on_mod_var((*reinterpret_cast< std::add_pointer_t<qEnum>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 13: _t->on_mod_var((*reinterpret_cast< std::add_pointer_t<qNode*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qVar*>>(_a[2]))); break;
        case 14: _t->keyPressEvent((*reinterpret_cast< std::add_pointer_t<QKeyEvent*>>(_a[1]))); break;
        case 15: _t->keyReleaseEvent((*reinterpret_cast< std::add_pointer_t<QKeyEvent*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< qNode* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< qNode* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< qNode* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< qNode* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< qNode* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< qNode* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< qNode* >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< qVar* >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< qNode* >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< qVar* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (qNode::*)(bool , qNode * );
            if (_t _q_method = &qNode::var_add_ok; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (qNode::*)(bool , qNode * );
            if (_t _q_method = &qNode::var_del_ok; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (qNode::*)(bool , qNode * );
            if (_t _q_method = &qNode::var_mod_ok; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (qNode::*)(qNode * );
            if (_t _q_method = &qNode::delete_node; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (qNode::*)(qNode * );
            if (_t _q_method = &qNode::select_node; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (qNode::*)(qNode * );
            if (_t _q_method = &qNode::name_change; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject *qNode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qNode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qNode.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QItemR"))
        return static_cast< QItemR*>(this);
    if (!strcmp(_clname, "qDesign"))
        return static_cast< qDesign*>(this);
    return QObject::qt_metacast(_clname);
}

int qNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void qNode::var_add_ok(bool _t1, qNode * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void qNode::var_del_ok(bool _t1, qNode * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void qNode::var_mod_ok(bool _t1, qNode * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void qNode::delete_node(qNode * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void qNode::select_node(qNode * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void qNode::name_change(qNode * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
