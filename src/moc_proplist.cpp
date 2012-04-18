/****************************************************************************
** Meta object code from reading C++ file 'proplist.h'
**
** Created: Wed Apr 18 12:26:09 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "proplist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'proplist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PropList[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      28,    9,    9,    9, 0x08,
      55,    9,    9,    9, 0x08,
      64,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PropList[] = {
    "PropList\0\0activate(QString)\0"
    "pClicked(QListWidgetItem*)\0hideMe()\0"
    "showMe()\0"
};

void PropList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PropList *_t = static_cast<PropList *>(_o);
        switch (_id) {
        case 0: _t->activate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->pClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->hideMe(); break;
        case 3: _t->showMe(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PropList::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PropList::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PropList,
      qt_meta_data_PropList, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PropList::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PropList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PropList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PropList))
        return static_cast<void*>(const_cast< PropList*>(this));
    return QWidget::qt_metacast(_clname);
}

int PropList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void PropList::activate(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
