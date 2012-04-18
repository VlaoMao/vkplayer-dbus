/****************************************************************************
** Meta object code from reading C++ file 'parser.h'
**
** Created: Wed Apr 18 14:41:13 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "parser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'parser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Parser[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      28,    7,    7,    7, 0x05,
      48,   45,    7,    7, 0x05,
      91,   89,    7,    7, 0x05,
     117,    7,    7,    7, 0x05,
     134,    7,    7,    7, 0x05,
     151,    7,    7,    7, 0x05,
     167,   89,    7,    7, 0x05,
     199,   45,    7,    7, 0x05,
     228,    7,    7,    7, 0x05,
     251,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     267,    7,    7,    7, 0x08,
     297,    7,    7,    7, 0x08,
     309,   89,    7,    7, 0x08,
     334,    7,    7,    7, 0x08,
     352,  346,    7,    7, 0x0a,
     366,    7,    7,    7, 0x2a,
     377,    7,    7,    7, 0x0a,
     400,    7,    7,    7, 0x0a,
     418,  346,    7,    7, 0x0a,
     433,    7,    7,    7, 0x2a,
     445,   89,    7,    7, 0x0a,
     467,   89,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Parser[] = {
    "Parser\0\0putContent(QString)\0"
    "loginState(bool)\0,,\0"
    "queryList(QMap<int,QString>,QString,int)\0"
    ",\0putProps(QStringList,int)\0"
    "setShowLoading()\0setHideLoading()\0"
    "listLoaded(int)\0downloadProgress(qint64,qint64)\0"
    "setDownloadView(int,int,int)\0"
    "setDownloadQCount(int)\0allDownloaded()\0"
    "replyFinished(QNetworkReply*)\0dReadData()\0"
    "dProgress(qint64,qint64)\0dFinished()\0"
    "index\0doZaebis(int)\0doZaebis()\0"
    "setSearchText(QString)\0dDuplicates(bool)\0"
    "getListUn(int)\0getListUn()\0"
    "addToLibrary(int,int)\0addDownload(int,int)\0"
};

const QMetaObject Parser::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Parser,
      qt_meta_data_Parser, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Parser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Parser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Parser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Parser))
        return static_cast<void*>(const_cast< Parser*>(this));
    return QObject::qt_metacast(_clname);
}

int Parser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: putContent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: loginState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: queryList((*reinterpret_cast< QMap<int,QString>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: putProps((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: setShowLoading(); break;
        case 5: setHideLoading(); break;
        case 6: listLoaded((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 8: setDownloadView((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 9: setDownloadQCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: allDownloaded(); break;
        case 11: replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 12: dReadData(); break;
        case 13: dProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 14: dFinished(); break;
        case 15: doZaebis((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: doZaebis(); break;
        case 17: setSearchText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: dDuplicates((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: getListUn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: getListUn(); break;
        case 21: addToLibrary((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 22: addDownload((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void Parser::putContent(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Parser::loginState(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Parser::queryList(QMap<int,QString> _t1, QString _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Parser::putProps(QStringList _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Parser::setShowLoading()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void Parser::setHideLoading()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void Parser::listLoaded(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Parser::downloadProgress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Parser::setDownloadView(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Parser::setDownloadQCount(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Parser::allDownloaded()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}
QT_END_MOC_NAMESPACE
