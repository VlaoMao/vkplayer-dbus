/****************************************************************************
** Meta object code from reading C++ file 'tray.h'
**
** Created: Wed Apr 18 12:26:08 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tray.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tray.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SysTrayIcon[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_SysTrayIcon[] = {
    "SysTrayIcon\0\0sEvent(QEvent*)\0"
};

void SysTrayIcon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SysTrayIcon *_t = static_cast<SysTrayIcon *>(_o);
        switch (_id) {
        case 0: _t->sEvent((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SysTrayIcon::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SysTrayIcon::staticMetaObject = {
    { &QSystemTrayIcon::staticMetaObject, qt_meta_stringdata_SysTrayIcon,
      qt_meta_data_SysTrayIcon, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SysTrayIcon::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SysTrayIcon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SysTrayIcon::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SysTrayIcon))
        return static_cast<void*>(const_cast< SysTrayIcon*>(this));
    return QSystemTrayIcon::qt_metacast(_clname);
}

int SysTrayIcon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSystemTrayIcon::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void SysTrayIcon::sEvent(QEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_Tray[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,
      14,    5,    5,    5, 0x05,
      22,    5,    5,    5, 0x05,
      30,    5,    5,    5, 0x05,
      37,    5,    5,    5, 0x05,
      44,    5,    5,    5, 0x05,
      51,    5,    5,    5, 0x05,
      61,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      73,    5,    5,    5, 0x08,
     120,    5,    5,    5, 0x08,
     140,    5,    5,    5, 0x0a,
     155,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Tray[] = {
    "Tray\0\0showW()\0click()\0pause()\0next()\0"
    "prev()\0quit()\0wheelUp()\0wheelDown()\0"
    "trayClicked(QSystemTrayIcon::ActivationReason)\0"
    "catchEvent(QEvent*)\0setPauseIcon()\0"
    "setPlayIcon()\0"
};

void Tray::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Tray *_t = static_cast<Tray *>(_o);
        switch (_id) {
        case 0: _t->showW(); break;
        case 1: _t->click(); break;
        case 2: _t->pause(); break;
        case 3: _t->next(); break;
        case 4: _t->prev(); break;
        case 5: _t->quit(); break;
        case 6: _t->wheelUp(); break;
        case 7: _t->wheelDown(); break;
        case 8: _t->trayClicked((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 9: _t->catchEvent((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        case 10: _t->setPauseIcon(); break;
        case 11: _t->setPlayIcon(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Tray::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Tray::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Tray,
      qt_meta_data_Tray, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Tray::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Tray::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Tray::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Tray))
        return static_cast<void*>(const_cast< Tray*>(this));
    return QObject::qt_metacast(_clname);
}

int Tray::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Tray::showW()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Tray::click()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Tray::pause()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Tray::next()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Tray::prev()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void Tray::quit()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void Tray::wheelUp()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void Tray::wheelDown()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}
QT_END_MOC_NAMESPACE