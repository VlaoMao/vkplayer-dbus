#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <phonon/SeekSlider>
#include <phonon/VolumeSlider>

#include "parser.h"
#include "player.h"
#include "playlist.h"
#include "settingswindow.h"
#include "tray.h"
#include "proplist.h"

#include <QMainWindow>
#include <QListWidget>
#include <QComboBox>
#include <QListWidgetItem>
#include <QPushButton>
#include <QProgressBar>
#include <QTimer>
#include <QTreeView>
#include <QStandardItemModel>
#include <QKeyEvent>
#include <QLabel>
#include "dbus.h"


//namespace Ui {
//    class MainWindow;
//}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    void showNotify(QString, QString);
    QString appPath;
    QString version;


private:
                    /* OBJECTS */

    // Main application objects
    Parser *parser;
    Player *player;
    QCBAdapter* adapter;
    Tray *tray;
    SettingsWindow *sWindow;

    int curIndex;
    //int prevIndex;
    int mresultsIndex;
    QMap<int, QListWidgetItem *> listItems;
    QMap<int, PropList *> propLists;
    QMap<QString, QString> curSong;

    // Fonts presets
    QFont defaultTrack;
    QFont currentTrack;

    // UI widgets
    Phonon::SeekSlider *seekSlider;
    Phonon::VolumeSlider *volumeSlider;

    QPushButton *playButton;

    QPushButton *shuffleButton;
    QPushButton *repeatButton;
    QPushButton *saveMusic;

    QPushButton *settingsButton;
    QPushButton *aboutButton;
    QLabel *networkIcon;
    QPushButton *quitButton;

    QProgressBar *progressBar;
    QLabel *progressLabel;
    QLabel *l_CTime;
    QLabel *l_TTime;

    QLabel *messageLabel;

    QTabWidget *mainTabs;
    QMap<int, playList *> playLists;
    QMap<int, QLineEdit *> queryEdit;
    QMap<int, QPushButton *> refreshButtons;
    QMap<int, QPushButton *> moreResButtons;
    QPixmap queueIcon(int);

    QLabel *downloadLabel;
    QLabel *dCurTitle;
    QLabel *dQueue;
    QProgressBar *dBar;

    // Menu
    QMenu *listMenu;
    QMenu *addToListM;

    // Misc
    QTimer *cronTimer;

    // Variables
    int listCount;
    int topListIndex;
    bool lucidDetected;
    bool trayWheelTracks;
    bool notifyDisabled;

    QMap<int, QStandardItemModel *> models;

    int lastSelected;
    int prevListIndex;
    int prevIndex;
    QModelIndex lastSelectedQ;
    QMap <int, int> curSelected;

    bool isDPopupVis;

                    /* FUNCTIONS */
    void setupUi();
    void resizeEvent(QResizeEvent *rEvent);
    void updateWidgets();
    void createList(int type, QString tabName = "New list");
    void createMenus();

public slots:
    void playAction(QModelIndex);
    void test();
    void setSongView(QMap<QString, QString>, int, bool);
    void setState();
    void setBufferProgress(int, int);
    void icanDoZaebis();
    void loginState(bool);
    void loadMRresults();
    void showLoading();
    void hideLoading();
    void showMessage(QString);
    void hideMessage();
    void loadSettings();
    void setupList(int);
    void playSelected();
    void addDownload();
    void setDownloadView(int, int, int);
    void setDownloadQCount(int);
    void allDownloaded();
    void trayWheelUp();
    void trayWheelDown();
    void setProps(QStringList, int);
    void propClicked(QString);

private slots:
    void cron();
    void selectedChanged(QModelIndex);
    void listKeyEvents(QKeyEvent *);
    void plistMenu(QPoint);
    void addToQueue();
    void setQueueView(int, int, int);
    void addToLibrary();
    void deleteItem();
    void networkError(int);
    void setDownloadProgress(qint64, qint64);
    void showDPopup();
    void hideDPopup();
    void addToList();
    void s_Time(qint64);
    void s_TotalTime(qint64);
    void trayClick();
    void quitApp();
    void showAbout();
    void copy2Clipboard();
};

#endif // MAINWINDOW_H
