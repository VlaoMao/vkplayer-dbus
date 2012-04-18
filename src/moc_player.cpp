/****************************************************************************
** Meta object code from reading C++ file 'player.h'
**
** Created: Wed Apr 18 14:41:15 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "player.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'player.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Player[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

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
     205,    7,    7,    7, 0x05,
     226,    7,    7,    7, 0x05,
     246,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     258,    7,    7,    7, 0x0a,
     300,    7,    7,    7, 0x0a,
     316,    7,    7,    7, 0x0a,
     327,    7,    7,    7, 0x0a,
     338,    7,    7,    7, 0x0a,
     357,    7,    7,    7, 0x0a,
     364,   66,    7,    7, 0x0a,
     384,    7,    7,    7, 0x0a,
     406,    7,  401,    7, 0x0a,
     418,    7,    7,    7, 0x0a,
     434,    7,  401,    7, 0x0a,
     445,    7,    7,    7, 0x0a,
     481,    7,    7,    7, 0x08,
     496,    7,    7,    7, 0x08,
     507,    7,    7,    7, 0x08,
     519,   66,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Player[] = {
    "Player\0\0stateChanged()\0,,\0"
    "curSong(QMap<QString,QString>,int,bool)\0"
    ",\0bufferProgress(int,int)\0playSomething()\0"
    "setQueueView(int,int,int)\0networkError(int)\0"
    "tick(qint64)\0totalTimeChanged(qint64)\0"
    "play()\0pause()\0shuffleToggled(bool)\0"
    "repeatToggled(bool)\0muted(bool)\0"
    "setList(QMap<int,QMap<QString,QString> >)\0"
    "playPause(bool)\0playNext()\0playPrev()\0"
    "setSaveMusic(bool)\0cron()\0addToQueue(int,int)\0"
    "setShuffle(bool)\0bool\0isShuffle()\0"
    "setRepeat(bool)\0isRepeat()\0"
    "nError(QNetworkReply::NetworkError)\0"
    "playFinished()\0readData()\0rFinished()\0"
    "dProgress(qint64,qint64)\0"
};

const QMetaObject Player::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Player,
      qt_meta_data_Player, 0 }
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
        switch (_id) {
        case 0: stateChanged(); break;
        case 1: curSong((*reinterpret_cast< QMap<QString,QString>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: bufferProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: playSomething(); break;
        case 4: setQueueView((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: networkError((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: tick((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 7: totalTimeChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 8: play(); break;
        case 9: pause(); break;
        case 10: shuffleToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: repeatToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: muted((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: setList((*reinterpret_cast< QMap<int,QMap<QString,QString> >(*)>(_a[1]))); break;
        case 14: playPause((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: playNext(); break;
        case 16: playPrev(); break;
        case 17: setSaveMusic((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: cron(); break;
        case 19: addToQueue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 20: setShuffle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: { bool _r = isShuffle();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 22: setRepeat((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: { bool _r = isRepeat();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 24: nError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 25: playFinished(); break;
        case 26: readData(); break;
        case 27: rFinished(); break;
        case 28: dProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 29;
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

// SIGNAL 10
void Player::shuffleToggled(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void Player::repeatToggled(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void Player::muted(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_END_MOC_NAMESPACE
