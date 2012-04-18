/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed Apr 18 14:51:26 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
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

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
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
        switch (_id) {
        case 0: playAction((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: test(); break;
        case 2: setSongView((*reinterpret_cast< QMap<QString,QString>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 3: setState(); break;
        case 4: setBufferProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: icanDoZaebis(); break;
        case 6: loginState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: loadMRresults(); break;
        case 8: showLoading(); break;
        case 9: hideLoading(); break;
        case 10: showMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: hideMessage(); break;
        case 12: loadSettings(); break;
        case 13: setupList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: playSelected(); break;
        case 15: addDownload(); break;
        case 16: setDownloadView((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 17: setDownloadQCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: allDownloaded(); break;
        case 19: trayWheelUp(); break;
        case 20: trayWheelDown(); break;
        case 21: setProps((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 22: propClicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: cron(); break;
        case 24: selectedChanged((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 25: listKeyEvents((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 26: plistMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 27: addToQueue(); break;
        case 28: setQueueView((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 29: addToLibrary(); break;
        case 30: deleteItem(); break;
        case 31: networkError((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: setDownloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 33: showDPopup(); break;
        case 34: hideDPopup(); break;
        case 35: addToList(); break;
        case 36: s_Time((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 37: s_TotalTime((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 38: trayClick(); break;
        case 39: quitApp(); break;
        case 40: showAbout(); break;
        case 41: copy2Clipboard(); break;
        default: ;
        }
        _id -= 42;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
