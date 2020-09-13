/****************************************************************************
** Meta object code from reading C++ file 'utils.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../megazord/utils.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'utils.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GdbInterface_t {
    QByteArrayData data[8];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GdbInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GdbInterface_t qt_meta_stringdata_GdbInterface = {
    {
QT_MOC_LITERAL(0, 0, 12), // "GdbInterface"
QT_MOC_LITERAL(1, 13, 6), // "parsed"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 33), // "QVector<QVector<QVector<Qube>..."
QT_MOC_LITERAL(4, 55, 6), // "vector"
QT_MOC_LITERAL(5, 62, 14), // "onGDBConnected"
QT_MOC_LITERAL(6, 77, 12), // "gdbReadyRead"
QT_MOC_LITERAL(7, 90, 7) // "trigger"

    },
    "GdbInterface\0parsed\0\0"
    "QVector<QVector<QVector<Qube> > >\0"
    "vector\0onGDBConnected\0gdbReadyRead\0"
    "trigger"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GdbInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   37,    2, 0x0a /* Public */,
       6,    0,   38,    2, 0x0a /* Public */,
       7,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,

       0        // eod
};

void GdbInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GdbInterface *_t = static_cast<GdbInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->parsed((*reinterpret_cast< QVector<QVector<QVector<Qube> > >(*)>(_a[1]))); break;
        case 1: _t->onGDBConnected(); break;
        case 2: _t->gdbReadyRead(); break;
        case 3: { int _r = _t->trigger();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GdbInterface::*)(QVector<QVector<QVector<Qube>> > );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GdbInterface::parsed)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GdbInterface::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GdbInterface.data,
      qt_meta_data_GdbInterface,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GdbInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GdbInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GdbInterface.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GdbInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void GdbInterface::parsed(QVector<QVector<QVector<Qube>> > _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
