/****************************************************************************
** Meta object code from reading C++ file 'player.h'
**
** Created: Tue Apr 17 18:08:14 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "player.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'player.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Player[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      26,   23,    7,    7, 0x05,
      68,   66,    7,    7, 0x05,
      92,    7,    7,    7, 0x05,
     108,   23,    7,    7, 0x05,
     134,    7,    7,    7, 0x05,
     152,    7,    7,    7, 0x05,
     165,    7,    7,    7, 0x05,
     190,    7,    7,    7, 0x05,
     197,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     205,    7,    7,    7, 0x0a,
     247,    7,    7,    7, 0x0a,
     263,    7,    7,    7, 0x0a,
     274,    7,    7,    7, 0x0a,
     285,    7,    7,    7, 0x0a,
     304,    7,    7,    7, 0x0a,
     311,   66,    7,    7, 0x0a,
     331,    7,    7,    7, 0x0a,
     348,    7,    7,    7, 0x0a,
     364,    7,    7,    7, 0x0a,
     400,    7,    7,    7, 0x08,
     415,    7,    7,    7, 0x08,
     426,    7,    7,    7, 0x08,
     438,   66,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Player[] = {
    "Player\0\0stateChanged()\0,,\0"
    "curSong(QMap<QString,QString>,int,bool)\0"
    ",\0bufferProgress(int,int)\0playSomething()\0"
    "setQueueView(int,int,int)\0networkError(int)\0"
    "tick(qint64)\0totalTimeChanged(qint64)\0"
    "play()\0pause()\0setList(QMap<int,QMap<QString,QString> >)\0"
    "playPause(bool)\0playNext()\0playPrev()\0"
    "setSaveMusic(bool)\0cron()\0addToQueue(int,int)\0"
    "setShuffle(bool)\0setRepeat(bool)\0"
    "nError(QNetworkReply::NetworkError)\0"
    "playFinished()\0readData()\0rFinished()\0"
    "dProgress(qint64,qint64)\0"
};

void Player::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Player *_t = static_cast<Player *>(_o);
        switch (_id) {
        case 0: _t->stateChanged(); break;
        case 1: _t->curSong((*reinterpret_cast< QMap<QString,QString>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->bufferProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->playSomething(); break;
        case 4: _t->setQueueView((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->networkError((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->tick((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 7: _t->totalTimeChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 8: _t->play(); break;
        case 9: _t->pause(); break;
        case 10: _t->setList((*reinterpret_cast< QMap<int,QMap<QString,QString> >(*)>(_a[1]))); break;
        case 11: _t->playPause((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->playNext(); break;
        case 13: _t->playPrev(); break;
        case 14: _t->setSaveMusic((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->cron(); break;
        case 16: _t->addToQueue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 17: _t->setShuffle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->setRepeat((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->nError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 20: _t->playFinished(); break;
        case 21: _t->readData(); break;
        case 22: _t->rFinished(); break;
        case 23: _t->dProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Player::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Player::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Player,
      qt_meta_data_Player, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Player::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Player::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Player::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Player))
        return static_cast<void*>(const_cast< Player*>(this));
    return QObject::qt_metacast(_clname);
}

int Player::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void Player::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Player::curSong(QMap<QString,QString> _t1, int _t2, bool _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Player::bufferProgress(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Player::playSomething()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Player::setQueueView(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Player::networkError(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Player::tick(qint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Player::totalTimeChanged(qint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Player::play()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void Player::pause()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}
QT_END_MOC_NAMESPACE
