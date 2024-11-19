/****************************************************************************
** Meta object code from reading C++ file 'qPrompt.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../include/node/qPrompt.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qPrompt.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_qPrompt_t {
    uint offsetsAndSizes[20];
    char stringdata0[8];
    char stringdata1[4];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[4];
    char stringdata5[4];
    char stringdata6[5];
    char stringdata7[9];
    char stringdata8[9];
    char stringdata9[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_qPrompt_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_qPrompt_t qt_meta_stringdata_qPrompt = {
    {
        QT_MOC_LITERAL(0, 7),  // "qPrompt"
        QT_MOC_LITERAL(8, 3),  // "add"
        QT_MOC_LITERAL(12, 0),  // ""
        QT_MOC_LITERAL(13, 5),  // "qEnum"
        QT_MOC_LITERAL(19, 3),  // "del"
        QT_MOC_LITERAL(23, 3),  // "mod"
        QT_MOC_LITERAL(27, 4),  // "eval"
        QT_MOC_LITERAL(32, 8),  // "on_parse"
        QT_MOC_LITERAL(41, 8),  // "on_mandb"
        QT_MOC_LITERAL(50, 7)   // "on_math"
    },
    "qPrompt",
    "add",
    "",
    "qEnum",
    "del",
    "mod",
    "eval",
    "on_parse",
    "on_mandb",
    "on_math"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_qPrompt[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    4,   56,    2, 0x06,    1 /* Public */,
       4,    2,   65,    2, 0x06,    6 /* Public */,
       5,    4,   70,    2, 0x06,    9 /* Public */,
       6,    1,   79,    2, 0x06,   14 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   82,    2, 0x09,   16 /* Protected */,
       8,    0,   83,    2, 0x09,   17 /* Protected */,
       9,    0,   84,    2, 0x09,   18 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::QString, QMetaType::Double,    2,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject qPrompt::staticMetaObject = { {
    QMetaObject::SuperData::link<QEditL::staticMetaObject>(),
    qt_meta_stringdata_qPrompt.offsetsAndSizes,
    qt_meta_data_qPrompt,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_qPrompt_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<qPrompt, std::true_type>,
        // method 'add'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qEnum, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'del'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qEnum, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'mod'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qEnum, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'eval'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_parse'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_mandb'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_math'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void qPrompt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<qPrompt *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->add((*reinterpret_cast< std::add_pointer_t<qEnum>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4]))); break;
        case 1: _t->del((*reinterpret_cast< std::add_pointer_t<qEnum>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->mod((*reinterpret_cast< std::add_pointer_t<qEnum>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 3: _t->eval((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->on_parse(); break;
        case 5: _t->on_mandb(); break;
        case 6: _t->on_math(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (qPrompt::*)(qEnum , QString , QString , double );
            if (_t _q_method = &qPrompt::add; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (qPrompt::*)(qEnum , QString );
            if (_t _q_method = &qPrompt::del; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (qPrompt::*)(qEnum , QString , QString , QString );
            if (_t _q_method = &qPrompt::mod; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (qPrompt::*)(QString );
            if (_t _q_method = &qPrompt::eval; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *qPrompt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qPrompt::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qPrompt.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "qDesign"))
        return static_cast< qDesign*>(this);
    return QEditL::qt_metacast(_clname);
}

int qPrompt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QEditL::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void qPrompt::add(qEnum _t1, QString _t2, QString _t3, double _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void qPrompt::del(qEnum _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void qPrompt::mod(qEnum _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void qPrompt::eval(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
