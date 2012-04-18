/****************************************************************************
** Meta object code from reading C++ file 'dbus.h'
**
** Created: Wed Apr 18 12:31:32 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dbus.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCBAdapter[] = {

 // content:
       6,       // revision
       0,       // classname
       1,   14, // classinfo
       5,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // classinfo: key, value
      32,   11,

 // methods: signature, parameters, type, tag, flags
      49,   48,   48,   48, 0x02,
      61,   48,   48,   48, 0x02,
      72,   48,   48,   48, 0x02,
      83,   48,   48,   48, 0x02,
      96,   48,   48,   48, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_QCBAdapter[] = {
    "QCBAdapter\0DBus.VKplayer.Player\0"
    "D-Bus Interface\0\0PlayPause()\0PlayPrev()\0"
    "PlayNext()\0VolumeDown()\0VolumeUp()\0"
};

void QCBAdapter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCBAdapter *_t = static_cast<QCBAdapter *>(_o);
        switch (_id) {
        case 0: _t->PlayPause(); break;
        case 1: _t->PlayPrev(); break;
        case 2: _t->PlayNext(); break;
        case 3: _t->VolumeDown(); break;
        case 4: _t->VolumeUp(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QCBAdapter::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCBAdapter::staticMetaObject = {
    { &QDBusAbstractAdaptor::staticMetaObject, qt_meta_stringdata_QCBAdapter,
      qt_meta_data_QCBAdapter, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCBAdapter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCBAdapter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCBAdapter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCBAdapter))
        return static_cast<void*>(const_cast< QCBAdapter*>(this));
    return QDBusAbstractAdaptor::qt_metacast(_clname);
}

int QCBAdapter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
