/****************************************************************************
** Meta object code from reading C++ file 'dbus.h'
**
** Created: Wed Apr 18 14:51:29 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dbus.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCBAdapter[] = {

 // content:
       5,       // revision
       0,       // classname
       1,   14, // classinfo
      11,   16, // methods
       2,   71, // properties
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
     117,  107,   48,   48, 0x02,
     139,   48,  134,   48, 0x02,
     160,  151,   48,   48, 0x02,
     176,   48,  134,   48, 0x02,
     187,   48,   48,   48, 0x02,
     194,   48,   48,   48, 0x02,

 // properties: name, type, flags
     203,  134, 0x01095103,
     211,  134, 0x01095103,

       0        // eod
};

static const char qt_meta_stringdata_QCBAdapter[] = {
    "QCBAdapter\0DBus.VKplayer.Player\0"
    "D-Bus Interface\0\0PlayPause()\0PlayPrev()\0"
    "PlayNext()\0VolumeDown()\0VolumeUp()\0"
    "isShuffle\0setShuffle(bool)\0bool\0"
    "isShuffle()\0isRepeat\0setRepeat(bool)\0"
    "isRepeat()\0mute()\0unmute()\0shuffle\0"
    "repeat\0"
};

const QMetaObject QCBAdapter::staticMetaObject = {
    { &QDBusAbstractAdaptor::staticMetaObject, qt_meta_stringdata_QCBAdapter,
      qt_meta_data_QCBAdapter, 0 }
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
        switch (_id) {
        case 0: PlayPause(); break;
        case 1: PlayPrev(); break;
        case 2: PlayNext(); break;
        case 3: VolumeDown(); break;
        case 4: VolumeUp(); break;
        case 5: setShuffle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: { bool _r = isShuffle();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: setRepeat((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: { bool _r = isRepeat();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: mute(); break;
        case 10: unmute(); break;
        default: ;
        }
        _id -= 11;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = isShuffle(); break;
        case 1: *reinterpret_cast< bool*>(_v) = isRepeat(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setShuffle(*reinterpret_cast< bool*>(_v)); break;
        case 1: setRepeat(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
