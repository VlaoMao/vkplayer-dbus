/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed Apr 18 11:22:53 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      42,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      36,   11,   11,   11, 0x0a,
      46,   43,   11,   11, 0x0a,
      90,   11,   11,   11, 0x0a,
     103,  101,   11,   11, 0x0a,
     130,   11,   11,   11, 0x0a,
     145,   11,   11,   11, 0x0a,
     162,   11,   11,   11, 0x0a,
     178,   11,   11,   11, 0x0a,
     192,   11,   11,   11, 0x0a,
     206,   11,   11,   11, 0x0a,
     227,   11,   11,   11, 0x0a,
     241,   11,   11,   11, 0x0a,
     256,   11,   11,   11, 0x0a,
     271,   11,   11,   11, 0x0a,
     286,   11,   11,   11, 0x0a,
     300,   43,   11,   11, 0x0a,
     329,   11,   11,   11, 0x0a,
     352,   11,   11,   11, 0x0a,
     368,   11,   11,   11, 0x0a,
     382,   11,   11,   11, 0x0a,
     398,  101,   11,   11, 0x0a,
     424,   11,   11,   11, 0x0a,
     445,   11,   11,   11, 0x08,
     452,   11,   11,   11, 0x08,
     481,   11,   11,   11, 0x08,
     507,   11,   11,   11, 0x08,
     525,   11,   11,   11, 0x08,
     538,   43,   11,   11, 0x08,
     564,   11,   11,   11, 0x08,
     579,   11,   11,   11, 0x08,
     592,   11,   11,   11, 0x08,
     610,  101,   11,   11, 0x08,
     645,   11,   11,   11, 0x08,
     658,   11,   11,   11, 0x08,
     671,   11,   11,   11, 0x08,
     683,   11,   11,   11, 0x08,
     698,   11,   11,   11, 0x08,
     718,   11,   11,   11, 0x08,
     730,   11,   11,   11, 0x08,
     740,   11,   11,   11, 0x08,
     752,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0playAction(QModelIndex)\0"
    "test()\0,,\0setSongView(QMap<QString,QString>,int,bool)\0"
    "setState()\0,\0setBufferProgress(int,int)\0"
    "icanDoZaebis()\0loginState(bool)\0"
    "loadMRresults()\0showLoading()\0"
    "hideLoading()\0showMessage(QString)\0"
    "hideMessage()\0loadSettings()\0"
    "setupList(int)\0playSelected()\0"
    "addDownload()\0setDownloadView(int,int,int)\0"
    "setDownloadQCount(int)\0allDownloaded()\0"
    "trayWheelUp()\0trayWheelDown()\0"
    "setProps(QStringList,int)\0"
    "propClicked(QString)\0cron()\0"
    "selectedChanged(QModelIndex)\0"
    "listKeyEvents(QKeyEvent*)\0plistMenu(QPoint)\0"
    "addToQueue()\0setQueueView(int,int,int)\0"
    "addToLibrary()\0deleteItem()\0"
    "networkError(int)\0setDownloadProgress(qint64,qint64)\0"
    "showDPopup()\0hideDPopup()\0addToList()\0"
    "s_Time(qint64)\0s_TotalTime(qint64)\0"
    "trayClick()\0quitApp()\0showAbout()\0"
    "copy2Clipboard()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->playAction((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: _t->test(); break;
        case 2: _t->setSongView((*reinterpret_cast< QMap<QString,QString>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 3: _t->setState(); break;
        case 4: _t->setBufferProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->icanDoZaebis(); break;
        case 6: _t->loginState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->loadMRresults(); break;
        case 8: _t->showLoading(); break;
        case 9: _t->hideLoading(); break;
        case 10: _t->showMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->hideMessage(); break;
        case 12: _t->loadSettings(); break;
        case 13: _t->setupList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->playSelected(); break;
        case 15: _t->addDownload(); break;
        case 16: _t->setDownloadView((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 17: _t->setDownloadQCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->allDownloaded(); break;
        case 19: _t->trayWheelUp(); break;
        case 20: _t->trayWheelDown(); break;
        case 21: _t->setProps((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 22: _t->propClicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: _t->cron(); break;
        case 24: _t->selectedChanged((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 25: _t->listKeyEvents((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 26: _t->plistMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 27: _t->addToQueue(); break;
        case 28: _t->setQueueView((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 29: _t->addToLibrary(); break;
        case 30: _t->deleteItem(); break;
        case 31: _t->networkError((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->setDownloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 33: _t->showDPopup(); break;
        case 34: _t->hideDPopup(); break;
        case 35: _t->addToList(); break;
        case 36: _t->s_Time((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 37: _t->s_TotalTime((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 38: _t->trayClick(); break;
        case 39: _t->quitApp(); break;
        case 40: _t->showAbout(); break;
        case 41: _t->copy2Clipboard(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 42)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 42;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
