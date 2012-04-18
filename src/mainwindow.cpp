#include "mainwindow.h"
#include <QPropertyAnimation>

#include <QtGui>
#include <QProcess>
#include <QMenuBar>

MainWindow::MainWindow() : QMainWindow()
{
    setWindowIcon(QIcon(QPixmap(":/icons/app")));

    appPath = QDir::homePath() + "/.vkplayer";
    if(!QDir(appPath).exists())
        QDir().mkdir(appPath);
    appPath += "/";

    version = "0.8.16";

    topListIndex = 0;
    lastSelected = -1;
    prevListIndex = -1;
    curIndex = -1;
    lucidDetected = false;
    trayWheelTracks = false;

    #ifdef Q_OS_LINUX
    QStringList arguments;
    arguments << "-c";
    QProcess myProcess;
    myProcess.start("lsb_release", arguments);
    myProcess.waitForFinished();
    QString pOut = myProcess.readAll();
    lucidDetected = pOut.contains("lucid");
    #endif

    player = new Player();
    adapter = new QCBAdapter(qApp);
    adapter->SetPlayerPointer(player);
    QDBusConnection connection = QDBusConnection::connectToBus(QDBusConnection::SessionBus, "DBus.VKplayer.Player");
    if (connection.isConnected())
        printf("Connected to dbus\n");
    if (!connection.registerService("DBus.VKplayer.Player")) {
        printf("Unable to register service\n");
        exit(1);
    }
    if (!connection.registerObject("/Player", adapter, QDBusConnection::ExportAllContents)) {
        printf("Unable to register object\n");
        exit(1);
    }

    connect(player, SIGNAL(playSomething()), SLOT(playSelected()));
    connect(player, SIGNAL(setQueueView(int,int,int)), SLOT(setQueueView(int,int,int)));
    connect(player, SIGNAL(networkError(int)), SLOT(networkError(int)));
    connect(player, SIGNAL(curSong(QMap<QString,QString>, int, bool)), SLOT(setSongView(QMap<QString,QString>, int, bool)));
    connect(player, SIGNAL(stateChanged()), this, SLOT(setState()));
    connect(player, SIGNAL(bufferProgress(int, int)), this, SLOT(setBufferProgress(int, int)));
    connect(player, SIGNAL(tick(qint64)), SLOT(s_Time(qint64)));
    connect(player, SIGNAL(totalTimeChanged(qint64)), SLOT(s_TotalTime(qint64)));

    tray = new Tray(this);
    connect(tray, SIGNAL(wheelUp()), SLOT(trayWheelUp()));
    connect(tray, SIGNAL(wheelDown()), SLOT(trayWheelDown()));
    connect(tray, SIGNAL(click()), SLOT(trayClick()));
    connect(tray, SIGNAL(next()), player, SLOT(playNext()));
    connect(tray, SIGNAL(prev()), player, SLOT(playPrev()));
    connect(tray, SIGNAL(quit()), SLOT(quitApp()));
    connect(player, SIGNAL(play()), tray, SLOT(setPlayIcon()));
    connect(player, SIGNAL(pause()), tray, SLOT(setPauseIcon()));

    parser = new Parser(this);
    parser->appPath = appPath;
    connect(parser, SIGNAL(listLoaded(int)), SLOT(setupList(int)));
    connect(parser, SIGNAL(loginState(bool)), this, SLOT(loginState(bool)));
    connect(parser, SIGNAL(setShowLoading()), this, SLOT(showLoading()));
    connect(parser, SIGNAL(setHideLoading()), this, SLOT(hideLoading()));
    connect(parser, SIGNAL(downloadProgress(qint64,qint64)), SLOT(setDownloadProgress(qint64,qint64)));
    connect(parser, SIGNAL(setDownloadView(int,int,int)), SLOT(setDownloadView(int,int,int)));
    connect(parser, SIGNAL(setDownloadQCount(int)), SLOT(setDownloadQCount(int)));
    connect(parser, SIGNAL(allDownloaded()), SLOT(allDownloaded()));
    connect(parser, SIGNAL(putProps(QStringList,int)), SLOT(setProps(QStringList,int)));


    sWindow = new SettingsWindow();
    sWindow->appPath = appPath;
    sWindow->loadSettings();
    connect(sWindow, SIGNAL(settingsChange()), this, SLOT(loadSettings()));

    setupUi();
    connect(tray, SIGNAL(pause()), playButton, SLOT(click()));


    //Misc
    cronTimer = new QTimer(this);
    connect(cronTimer, SIGNAL(timeout()), this, SLOT(cron()));
    connect(cronTimer, SIGNAL(timeout()), player, SLOT(cron()));
    cronTimer->start(1000);

    loadSettings();
    parser->letsLogin();

    createMenus();

    createList(0, tr("Search"));
    if(parser->isOwnAccount()) {
        createList(1, tr("My audio"));
        createList(2, tr("Recommendations"));
    }
    createList(3, tr("MyList"));

    parser->loadPlayList();

    player->parser = parser;

    updateWidgets();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupUi()
{
    // Setup fonts
    //defaultTrack.setPixelSize(11);
    //currentTrack.setPixelSize(12);
    currentTrack.setBold(true);

    // UI
    this->setWindowTitle("VKPlayer");

    QWidget *cWidget = new QWidget();
    this->setGeometry(QRect(300, 100, 700, 500));

    mainTabs = new QTabWidget(this);
    // FIXME mainTabs->setTabsClosable(true);

    QGridLayout *mainLayout = new QGridLayout();

    mainLayout->addWidget(mainTabs, 0, 0);

    // Loading animation
    QMovie *progressMovie = new QMovie(":/icons/progress");
    progressMovie->start();
    progressLabel = new QLabel(mainTabs);
    progressLabel->setMovie(progressMovie);
    progressLabel->hide();

    // Message label
    messageLabel = new QLabel(mainTabs);
    messageLabel->setHidden(true);
    messageLabel->setFixedHeight(30);
    messageLabel->setFixedWidth(250);
    messageLabel->setAlignment(Qt::AlignCenter);
    messageLabel->setStyleSheet("border-radius: 10px; background-color: rgba(55, 55, 55, 210); color: #fff; font-weight: bold; font-size: 14px;");

    downloadLabel = new QLabel(mainTabs);
    downloadLabel->setFixedHeight(100);
    downloadLabel->setFixedWidth(300);
    downloadLabel->setObjectName("downloadLabel");
    downloadLabel->setStyleSheet("QLabel#downloadLabel {border-radius: 10px; border-bottom-right-radius: 0px; border-bottom: none; background-color: rgba(55, 55, 55, 210); color: #fff; font-size: 12px;}");
    downloadLabel->setVisible(false);
    dBar = new QProgressBar(downloadLabel);
    dBar->setMaximum(1);
    dBar->setValue(0);
    dBar->setStyleSheet(":horizontal {border-radius: 0px; background: #BDBDBD;} ::chunk:horizontal { background: #000;}");
    dBar->setTextVisible(false);
    dBar->setFixedHeight(3);

    QLabel *dTitleLabel = new QLabel("<b>" + tr("DOWNLOADING") + "</b>", downloadLabel);
    dTitleLabel->setObjectName("dTitleLabel");
    dTitleLabel->setStyleSheet("QLabel#dTitleLabel {border-radius: 10px; border-bottom-right-radius: 0px; border-bottom-left-radius: 0px; background-color: rgba(55, 55, 55, 210); color: #fff; font-weight: bold;  font-size: 11px;}");
    dTitleLabel->setGeometry(0, 0, downloadLabel->width(), 20);
    dTitleLabel->setAlignment(Qt::AlignCenter);

    dCurTitle = new QLabel("Ac/Dc<br>Back in Black", downloadLabel);
    dCurTitle->setStyleSheet("color: #fff; font-size: 11px;");
    dCurTitle->setAlignment(Qt::AlignCenter);
    dCurTitle->setGeometry(0, 30, downloadLabel->width(), 30);

    dQueue = new QLabel("In queue: 0", downloadLabel);
    dQueue->setStyleSheet("color: #bbb; font-size: 11px;");
    dQueue->setAlignment(Qt::AlignCenter);
    dQueue->setGeometry(0, downloadLabel->height() - 25, downloadLabel->width(), 20);

    isDPopupVis = false;

    // Progress bar
    progressBar = new QProgressBar();
    progressBar->setTextVisible(false);
    QString sSheet = ":horizontal {border-radius: 0px; background: #BDBDBD;} ::chunk:horizontal { background: #575757;}";
    progressBar->setStyleSheet(sSheet);
    progressBar->setFixedHeight(2);
    //mainLayout->addWidget(progressBar);

    QGridLayout *seekLayout = new QGridLayout();

    QString tl_Style = "color: #585858; font-size: 9px;";
    l_CTime = new QLabel("0:00");
    l_CTime->setFixedWidth(30);
    l_CTime->setAlignment(Qt::AlignCenter);
    l_CTime->setStyleSheet(tl_Style);
    seekLayout->addWidget(l_CTime, 0, 0);

    // Seek slider
    seekSlider = new Phonon::SeekSlider();
    seekSlider->setMediaObject(player->mediaObject);
    int sliderHeight;
    QString sliderSheet;
    if(lucidDetected) {
        sliderHeight = 13;
        sliderSheet = "::groove:horizontal {background:  transparent;}\n\n::handle:horizontal { background-color: #808080; height: 9px; width: 14px; margin-bottom: 4px; }";
    } else {
        sliderHeight = 12;
        sliderSheet = "::groove:horizontal {background:  transparent;}\n\n::handle:horizontal { \nbackground: #808080;\nheight: 8px;\nwidth: 14px;\nmargin-bottom: 7px;\n}";
    }
    seekSlider->setFixedHeight(sliderHeight);
    seekSlider->setStyleSheet(sliderSheet);
    seekSlider->setIconVisible(false);
    seekLayout->addWidget(seekSlider, 0, 1);
    seekLayout->addWidget(progressBar, 0, 1);

    l_TTime = new QLabel("0:00");
    l_TTime->setFixedWidth(30);
    l_TTime->setAlignment(Qt::AlignCenter);
    l_TTime->setStyleSheet(tl_Style);
    seekLayout->addWidget(l_TTime, 0, 2);

    mainLayout->addLayout(seekLayout, 1, 0);

    // Bottom layout

    // Player buttons
    playButton = new QPushButton("");
    playButton->setMinimumWidth(80);
    playButton->setMinimumHeight(40);
    playButton->setCheckable(true);
    QIcon playIcon;
    playIcon.addPixmap(QPixmap(":/icons/big_pause"), QIcon::Normal, QIcon::On);
    playIcon.addPixmap(QPixmap(":/icons/big_play"), QIcon::Normal, QIcon::Off);
    playButton->setIcon(playIcon);
    playButton->setIconSize(QSize(24,24));

    QPushButton *prevButton = new QPushButton(QPixmap(":/icons/prev"), "");
    QPushButton *nextButton = new QPushButton(QPixmap(":/icons/next"), "");

    // Shuffle & repeat
    QIcon shuffleIcon;
    shuffleIcon.addPixmap(QPixmap(":/icons/shuffle"), QIcon::Normal, QIcon::On);
    shuffleIcon.addPixmap(QPixmap(":/icons/shuffle_off"), QIcon::Normal, QIcon::Off);
    shuffleButton = new QPushButton(shuffleIcon, "");
    shuffleButton->setFlat(true);
    shuffleButton->setIconSize(QSize(24,24));
    shuffleButton->setMaximumWidth(24);
    shuffleButton->setMaximumHeight(24);
    shuffleButton->setCheckable(true);
    shuffleButton->setStyleSheet("QPushButton {border: none;}");
    shuffleButton->setToolTip(tr("Shuffle current playlist"));

    QIcon repeatIcon;
    repeatIcon.addPixmap(QPixmap(":/icons/repeat"), QIcon::Normal, QIcon::On);
    repeatIcon.addPixmap(QPixmap(":/icons/repeat_off"), QIcon::Normal, QIcon::Off);
    repeatButton = new QPushButton(repeatIcon, "");
    repeatButton->setFlat(true);
    repeatButton->setIconSize(QSize(24,24));
    repeatButton->setMaximumWidth(24);
    repeatButton->setMaximumHeight(24);
    repeatButton->setCheckable(true);
    repeatButton->setStyleSheet("QPushButton {border: none;}");
    repeatButton->setToolTip(tr("Repeat current track"));

    // Setup bottom layout
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(prevButton);
    bottomLayout->addWidget(playButton);
    bottomLayout->addWidget(nextButton);
    bottomLayout->addSpacing(20);
    bottomLayout->addWidget(shuffleButton);
    bottomLayout->addWidget(repeatButton);

    QSpacerItem *bottomSpacer = new QSpacerItem(100,0, QSizePolicy::Maximum);

    QIcon saveMusicIcon;
    saveMusicIcon.addPixmap(QPixmap(":/icons/save"), QIcon::Normal, QIcon::On);
    saveMusicIcon.addPixmap(QPixmap(":/icons/save_off"), QIcon::Normal, QIcon::Off);
    saveMusic = new QPushButton(saveMusicIcon, "");
    saveMusic->setFlat(true);
    saveMusic->setIconSize(QSize(16,16));
    saveMusic->setMaximumWidth(16);
    saveMusic->setMaximumHeight(16);
    saveMusic->setCheckable(true);
    saveMusic->setStyleSheet("QPushButton {border: none;}");
    saveMusic->setToolTip(tr("Save music to folder while playing"));

    bottomLayout->addSpacerItem(bottomSpacer);
    bottomLayout->addWidget(saveMusic);

    // Volume button
    volumeSlider = new Phonon::VolumeSlider();
    volumeSlider->setAudioOutput(player->audioOutput);
    volumeSlider->setMaximumWidth(150);
    bottomLayout->addWidget(volumeSlider);

    // Settings button
    settingsButton = new QPushButton(QPixmap(":/icons/config"), "");
    settingsButton->setIconSize(QSize(32,32));
    settingsButton->setMaximumWidth(32);
    settingsButton->setMaximumHeight(32);
    bottomLayout->addWidget(settingsButton);

    // About button
    aboutButton = new QPushButton(QPixmap(":/icons/info"), "");
    aboutButton->setIconSize(QSize(32,32));
    aboutButton->setMaximumWidth(32);
    aboutButton->setMaximumHeight(32);
    bottomLayout->addWidget(aboutButton);
    connect(aboutButton, SIGNAL(clicked()), SLOT(showAbout()));

    // Quit button
    quitButton = new QPushButton(QPixmap(":/icons/off"), "", mainTabs);
    quitButton->setIconSize(QSize(20,20));
    quitButton->setMaximumWidth(20);
    quitButton->setMaximumHeight(20);
    quitButton->setGeometry(667, 0, quitButton->width(), quitButton->height());
    quitButton->hide();

    connect(quitButton, SIGNAL(clicked()), SLOT(quitApp()));

    // FIXME bottomLayout->addWidget(quitButton);

    networkIcon = new QLabel();
    networkIcon->setPixmap(QPixmap(":icons/offline"));
    bottomLayout->addWidget(networkIcon);

    mainLayout->addLayout(bottomLayout, 4, 0);

    cWidget->setLayout(mainLayout);
    setCentralWidget(cWidget);

    connect(playButton, SIGNAL(clicked(bool)), player, SLOT(playPause(bool)));
    connect(prevButton, SIGNAL(clicked()), player, SLOT(playPrev()));
    connect(nextButton, SIGNAL(clicked()), player, SLOT(playNext()));

    connect(shuffleButton, SIGNAL(clicked(bool)), player, SLOT(setShuffle(bool)));
    connect(player,SIGNAL(shuffleToggled(bool)),shuffleButton,SLOT(setChecked(bool)));
    connect(repeatButton, SIGNAL(clicked(bool)), player, SLOT(setRepeat(bool)));
    connect(player,SIGNAL(repeatToggled(bool)),repeatButton,SLOT(setChecked(bool)));
    connect(saveMusic, SIGNAL(clicked(bool)), player, SLOT(setSaveMusic(bool)));
    connect(settingsButton, SIGNAL(clicked()), sWindow, SLOT(show()));
}


void MainWindow::playAction(QModelIndex index)
{
        qDebug() << "QModelIndex: " << index;
        qDebug() << "PlayAction, index.row: " << index.row();
    curIndex = index.row();
    int listIndex = lastSelected;

    if(!player->listSync || player->currentListIndex != listIndex) {
        player->setList(parser->sources[listIndex]);
        player->currentListIndex = listIndex;

        if(player->curIndex != -1) {
            for(int i = 1; i < 4; i++) {
                models[listIndex]->item(player->curIndex, i)->setBackground(QBrush(QColor("#fff")));
                models[listIndex]->item(player->curIndex, i)->setFont(defaultTrack);
            }
        }
    }
    player->playIndex(index.row());
}

void MainWindow::test()
{
    qDebug() << "!!!TEST!!!";
    showMessage("Test message, bleat'");
}

void MainWindow::setSongView(QMap<QString, QString> song, int index, bool autoNext)
{

    int listIndex = player->currentListIndex;

    if(player->listSync) {
        curSong = song;

        models[listIndex]->item(index, 0)->setIcon(QIcon(QPixmap(":/icons/list_play")));

        for(int i = 0; i < 4; i++) {
            models[listIndex]->item(index, i)->setBackground(QBrush(QColor("#A7C39C")));
            models[listIndex]->item(index, i)->setFont(currentTrack);
        }
        playLists[listIndex]->scrollTo(models[listIndex]->index(index, 0));

        if(prevListIndex > -1 && prevIndex != index && models[prevListIndex]->rowCount() >= prevIndex) {
            for(int i = 0; i < 4; i++) {
                models[prevListIndex]->item(prevIndex, i)->setBackground(QBrush(QColor("#fff")));
                models[prevListIndex]->item(prevIndex, i)->setFont(defaultTrack);
            }
            models[prevListIndex]->item(prevIndex, 0)->setIcon(QIcon());
        }

        for(int i=0; i<topListIndex; i++) {
            mainTabs->setTabIcon(i, QIcon(QPixmap(":/icons/big_pause")));
        }
        mainTabs->setTabIcon(listIndex, QIcon(QPixmap(":/icons/big_play")));

        prevListIndex = listIndex;
        prevIndex = index;
    }

    this->setWindowTitle(song["title"] + " - " + song["artist"]);

    if(autoNext)
        showNotify(song["artist"], song["title"]);
}

void MainWindow::setState()
{
    if(player->curState == Player::PLAY)
        playButton->setChecked(true);

    if(player->curState == Player::STOPED)
        playButton->setChecked(false);
}

void MainWindow::showNotify(QString name, QString text)
{
    #ifdef Q_OS_LINUX
    if(!notifyDisabled) {
        QStringList arguments;
        arguments << "-i" << "vkplayer.png";
        arguments << name << text;
        QProcess* myProcess = new QProcess(this);
        myProcess->start("notify-send", arguments);
    }
    #endif
}

void MainWindow::setBufferProgress(int curValue, int totalValue)
{
    if(totalValue + totalValue < 0) {
        QString sSheet = ":horizontal {border-radius: 0px; background: #BDBDBD;} ::chunk:horizontal { background: #818181;}";
        progressBar->setStyleSheet(sSheet);
        progressBar->setMaximum(1);
        progressBar->setValue(1);
    } else {
        QString sSheet = ":horizontal {border-radius: 0px; background: #BDBDBD;} ::chunk:horizontal { background: #575757;}";
        progressBar->setStyleSheet(sSheet);
        progressBar->setMaximum(totalValue);
        progressBar->setValue(curValue);
    }
}

void MainWindow::icanDoZaebis()
{

}

void MainWindow::loginState(bool state)
{
    QString strOnline = tr("Online");
    QString strOffline = tr("Offline");
    if(state) {
        networkIcon->setPixmap(QPixmap(":icons/online"));
        if(parser->vkMyAcc)
            networkIcon->setToolTip(strOnline + " :: " + parser->vkLogin);
        else
            networkIcon->setToolTip(strOnline + " :: " + tr("default account"));
    } else {
        networkIcon->setPixmap(QPixmap(":icons/offline"));
        networkIcon->setToolTip(strOffline + " :: " + tr("network or login problems"));
    }

}

void MainWindow::cron()
{

}

void MainWindow::loadMRresults()
{
    int index = sender()->property("lid").toInt();
    moreResButtons[index]->setEnabled(false);
}

void MainWindow::selectedChanged(QModelIndex index)
{
        qDebug() << "Selected Changed";
    int listIndex = sender()->property("lid").toInt();
    curSelected[listIndex] = index.row();
    lastSelected = listIndex;
    lastSelectedQ = index;
}

void MainWindow::listKeyEvents(QKeyEvent *event)
{
    //int index = sender()->property("lid").toInt();

    switch(event->nativeScanCode()) {
        case 24: // Key Q
            addToQueue();
        break;

        case 40: // Key D
            addDownload();
        break;

        case 119: // Key delete
            deleteItem();
        break;

        default:
            //qDebug() << event->nativeScanCode();
        break;
    }
}

void MainWindow::showLoading()
{
    progressLabel->setGeometry((progressLabel->parentWidget()->width() / 2) - 75, progressLabel->parentWidget()->height() / 2, 149, 8);
    progressLabel->movie()->start();
    progressLabel->show();
}

void MainWindow::hideLoading()
{
    progressLabel->movie()->stop();
    progressLabel->hide();
}

void MainWindow::setupList(int index)
{
    bool isAdd;
    int addCount = -1;

    if(parser->listsConf[index]["d"].toInt() == 1) {
        parser->listsConf[index]["d"] = "0";
        player->playList = parser->sources[index];
    } else {

        if(player->currentListIndex == index)
            player->listSync = false;
    }

    if(parser->listsConf[index]["add"].toInt() == 0) {
        isAdd = false;
        models[index]->clear();
    } else {
        isAdd = true;
        addCount = parser->listsConf[index]["addCount"].toInt();
    }
    models[index]->setRowCount(parser->sources[index].size());

    models[index]->setColumnCount(4);

    models[index]->setHeaderData( 0, Qt::Horizontal, " ");
    models[index]->setHeaderData( 1, Qt::Horizontal, "#");
    models[index]->setHeaderData( 2, Qt::Horizontal, tr("Artist") + " - " + tr("Track"));
    models[index]->setHeaderData( 3, Qt::Horizontal, "m:s");
//    models[index]->setHeaderData( 4, Qt::Horizontal, "kb/s");

    QMapIterator< int, QMap<QString, QString> > i(parser->sources[index]);
    int ii = 0;

    while (i.hasNext()) {
        i.next();

        if((isAdd && ii > (parser->sources[index].size() - addCount) - 1) || !isAdd) {
            models[index]->setData( models[index]->index( ii, 0 ), "", Qt::DisplayRole);
            models[index]->setData( models[index]->index( ii, 1 ), QString::number(ii+1) + ".",    Qt::DisplayRole);
            models[index]->setData( models[index]->index( ii, 2 ), i.value()["artist"]+" - "+i.value()["title"],    Qt::DisplayRole );
            models[index]->setData( models[index]->index( ii, 3 ), i.value()["duration"], Qt::DisplayRole );
//            models[index]->setData( models[index]->index( ii, 4 ), i.value()["opt5"]+" kb/s",    Qt::DisplayRole );
            models[index]->item(ii, 1)->setFont(defaultTrack);
            models[index]->item(ii, 2)->setFont(defaultTrack);
            models[index]->item(ii, 2)->setToolTip(i.value()["artist"]+" - "+i.value()["title"]);
            models[index]->item(ii, 3)->setFont(defaultTrack);
//            models[index]->item(ii, 4)->setFont(defaultTrack);

            models[index]->item(ii, 1)->setForeground(QBrush(QColor("#A0A0A0")));
        }
        ++ii;
    }

    playLists[index]->setStyleSheet("::item {height: 20px;}");

    playLists[index]->setColumnWidth(0, 20);
    playLists[index]->setColumnWidth(1, 30);
    playLists[index]->setColumnWidth(2, 550);
    //playLists[index]->setColumnWidth(3, 50);
//    playLists[index]->setColumnWidth(4, 50);

    if(parser->listsConf[index]["more"].toInt() == 1)
        moreResButtons[index]->setEnabled(true);

    if(isAdd && player->currentListIndex == index)
        player->playList = parser->sources[index];
}

void MainWindow::loadSettings()
{
    QSettings settings(appPath+"settings.ini", QSettings::IniFormat);

    settings.beginGroup("settingsw");

    QString sPath = settings.value("app/savePath", "/music").toString() + "/";
    parser->savePath = sPath;
    player->savePath = sPath;
    player->setBufferOff(settings.value("app/bufferOff").toBool());
    saveMusic->setEnabled(!player->isBufferOff());

    if(settings.value("app/close2Tray").toBool())
        QApplication::setQuitOnLastWindowClosed(false);
    else
        QApplication::setQuitOnLastWindowClosed(true);

    if(settings.value("app/wheelAction").toInt() == 2)
        trayWheelTracks = true;

    if(settings.value("app/wheelAction").toInt() == 1)
        trayWheelTracks = false;

    parser->vkMyAcc = settings.value("acc/myacc").toBool();
    notifyDisabled = settings.value("app/notifyDisable").toBool();

    if(settings.value("acc/myacc").toBool()) {
        parser->vkLogin = settings.value("acc/login", "0").toString();
        parser->vkPass = settings.value("acc/pass", "0").toString();
    }
    settings.endGroup();
}

void MainWindow::createList(int type, QString tabName)
{
    int index = topListIndex++;
    parser->listsConf[index]["type"] = QString::number(type);
    parser->listsConf[index]["dDuplicates"] = "1";
    parser->listsConf[index]["title"] = tabName;

    // Setup objects
    models[index] = new QStandardItemModel();

    // Setup tab widget
    QWidget *tabWidget = new QWidget(mainTabs);
    QGridLayout *mainLayout = new QGridLayout();
    mainTabs->addTab(tabWidget, QIcon(QPixmap(":/icons/big_pause")), tabName);
    updateWidgets();


    // Top layout
    QHBoxLayout *topLayout = new QHBoxLayout();
    if(type == 0) {
        queryEdit[index] = new QLineEdit(this);
        queryEdit[index]->setEnabled(false);
        queryEdit[index]->setFixedHeight(25);
        queryEdit[index]->setStyleSheet("QLineEdit{padding-left: 17px; padding-right: 20px;}");
        queryEdit[index]->setProperty("lid", index);
        queryEdit[index]->setProperty("more", 0);
        connect(parser, SIGNAL(loginState(bool)), queryEdit[index], SLOT(setEnabled(bool)));
        connect(queryEdit[index], SIGNAL(textChanged(QString)), parser, SLOT(setSearchText(QString)));
        connect(queryEdit[index], SIGNAL(returnPressed()), parser, SLOT(doZaebis()));
        connect(queryEdit[index], SIGNAL(returnPressed()), models[index], SLOT(revert()));
        //connect(queryCombos[index], SIGNAL(editingFinished()), this, SLOT(queryFinished()));

        QLabel *searchIcon = new QLabel(queryEdit[index]);
        searchIcon->setPixmap(QPixmap(":/icons/search"));
        searchIcon->setGeometry(7, 6, 11, 11);

        // PropNadList
        propLists[index] = new PropList(mainTabs);
        propLists[index]->setGeometry(50, 53, 450, 1);
        propLists[index]->setProperty("lid", index);
        propLists[index]->setDaddy(queryEdit[index]);
        connect(propLists[index], SIGNAL(activate(QString)), SLOT(propClicked(QString)));
        //propList->setGeometry(queryCombos[index]->pos().x(), queryCombos[index]->pos().y()+queryCombos[index]->height(), queryCombos[index]->width(), 50);
        //bottomLayout->addWidget(propList);


        moreResButtons[index] = new QPushButton(tr("More results"));
        moreResButtons[index]->setEnabled(false);
        moreResButtons[index]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        moreResButtons[index]->setProperty("lid", index);
        moreResButtons[index]->setProperty("more", 1);
        connect(moreResButtons[index], SIGNAL(clicked()), parser, SLOT(doZaebis()));
        connect(moreResButtons[index], SIGNAL(clicked()), this, SLOT(loadMRresults()));

        QIcon filterIcon;
        filterIcon.addPixmap(QPixmap(":/icons/filter"), QIcon::Normal, QIcon::On);
        filterIcon.addPixmap(QPixmap(":/icons/filter_off"), QIcon::Normal, QIcon::Off);
        QPushButton *dDuplicates = new QPushButton(filterIcon, "");
        dDuplicates->setFlat(true);
        dDuplicates->setIconSize(QSize(16,16));
        dDuplicates->setMaximumWidth(16);
        dDuplicates->setMaximumHeight(16);
        dDuplicates->setCheckable(true);
        dDuplicates->setStyleSheet("QPushButton {border: none;}");
        dDuplicates->setToolTip(tr("Delete duplicates from search results"));
        dDuplicates->setChecked(true);
        connect(dDuplicates, SIGNAL(clicked(bool)), parser, SLOT(dDuplicates(bool)));

        topLayout->addWidget(queryEdit[index]);
        topLayout->addWidget(moreResButtons[index]);
        topLayout->addWidget(dDuplicates);

    }

    if(type == 1 || type == 2) {
        QPushButton *refreshButton = new QPushButton(tr("Refresh list"));
        refreshButton->setProperty("lid", index);
        topLayout->addWidget(refreshButton);

        connect(refreshButton, SIGNAL(clicked()), parser, SLOT(getListUn()));
    }

    mainLayout->addLayout(topLayout, 0, 0);

    // Playlist layout
    playLists[index] = new playList(this);
    playLists[index]->setEditTriggers(QAbstractItemView::NoEditTriggers);
    playLists[index]->setRootIsDecorated(false);
    playLists[index]->setProperty("lid", index);
    playLists[index]->setModel(models[index]);

    connect(playLists[index], SIGNAL(activated(QModelIndex)), this, SLOT(playAction(QModelIndex)));
    connect(playLists[index], SIGNAL(pressed(QModelIndex)), this, SLOT(selectedChanged(QModelIndex)));
    connect(playLists[index], SIGNAL(kEvent(QKeyEvent *)), this, SLOT(listKeyEvents(QKeyEvent *)));

    playLists[index]->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(playLists[index], SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(plistMenu(const QPoint)));

    mainLayout->addWidget(playLists[index], 1, 0);

    tabWidget->setLayout(mainLayout);

    if(type == 3) {
        QAction *addToListA = new QAction(tr("Add to %1").arg(tabName) , this);
        addToListA->setProperty("lid", index);
        connect(addToListA, SIGNAL(triggered()), SLOT(addToList()));

        addToListM->addAction(addToListA);
    }
}

void MainWindow::plistMenu(const QPoint point)
{
    int index = sender()->parent()->property("lid").toInt();
    listMenu->exec(playLists[index]->mapToGlobal(point));
}

void MainWindow::createMenus()
{
    QAction *downloadA = new QAction(QIcon(QPixmap(":/icons/download")), tr("Download"), this);
    downloadA->setShortcut(QKeySequence("D"));
    connect(downloadA, SIGNAL(triggered()), SLOT(addDownload()));

    QAction *addToQueueA = new QAction(QIcon(QPixmap(":/icons/current")), tr("Add to queue"), this);
    addToQueueA->setShortcut(QKeySequence("Q"));
    connect(addToQueueA, SIGNAL(triggered()), SLOT(addToQueue()));

    QAction *addToLibraryA = new QAction(QIcon(QPixmap(":/icons/toaudio")), tr("Add to MyAudio"), this);
    connect(addToLibraryA, SIGNAL(triggered()), SLOT(addToLibrary()));

    addToListM = new QMenu(tr("Add to list"), this);
    addToListM->setIcon(QIcon(QPixmap(":/icons/tolist")));

    QAction *deleteFromListA = new QAction(QIcon(QPixmap(":/icons/del")), tr("Delete"), this);;
    deleteFromListA->setShortcut(QKeySequence("Del"));
    connect(deleteFromListA, SIGNAL(triggered()), this, SLOT(deleteItem()));

    QAction *copy2ClipA = new QAction(QIcon(QPixmap(":/icons/copy")), tr("Copy title"), this);
    connect(copy2ClipA, SIGNAL(triggered()), SLOT(copy2Clipboard()));


    listMenu = new QMenu(this);

    listMenu->addAction(addToQueueA);
    listMenu->addSeparator();
    listMenu->addAction(downloadA);
    listMenu->addMenu(addToListM);
    listMenu->addAction(deleteFromListA);
    listMenu->addSeparator();
    listMenu->addAction(copy2ClipA);
    listMenu->addAction(addToLibraryA);
}

void MainWindow::playSelected()
{
    if(lastSelected > -1) {
        playAction(lastSelectedQ);
    }else{
            QModelIndex index = playLists[0]->model()->index(0,2);
            lastSelected = 0;
            lastSelectedQ = index;
            playAction(lastSelectedQ);
        }
}

void MainWindow::addToQueue()
{
    player->addToQueue(lastSelected, curSelected[lastSelected]);
}

void MainWindow::setQueueView(int listIndex, int itemIndex, int queueIndex)
{
    if(queueIndex > 0)
        models[listIndex]->item(itemIndex, 0)->setIcon(QIcon(queueIcon(queueIndex)));
    else
        models[listIndex]->item(itemIndex, 0)->setIcon(QIcon());
}


void MainWindow::addToLibrary()
{
    if(parser->vkMyAcc) {
        parser->addToLibrary(lastSelected, curSelected[lastSelected]);
        showMessage(tr("Added to MyAudio"));
    } else {
        QMessageBox::information(this, tr("o.O"), tr("Trollo-lo! For adding to VK audio library, you must use your own VK account.<br>You can setup an account in settings.<br>"));
    }
}


void MainWindow::showMessage(QString text)
{
    QRect startPos(-messageLabel->width(), messageLabel->parentWidget()->height() / 2, 149, 8);
    QRect endPos(-10, messageLabel->parentWidget()->height() / 2, 149, 8);

    messageLabel->setText(text);
    messageLabel->setHidden(false);

    QPropertyAnimation *animation = new QPropertyAnimation(messageLabel, "geometry");
    animation->setDuration(150);
    animation->setStartValue(startPos);
    animation->setEndValue(endPos);
    animation->start();

    QTimer::singleShot(2000, this, SLOT(hideMessage()));
}

void MainWindow::hideMessage()
{

    QRect endPos(-messageLabel->width(), messageLabel->parentWidget()->height() / 2, 149, 8);
    QRect startPos(-10, messageLabel->parentWidget()->height() / 2, 149, 8);

    QPropertyAnimation *animation = new QPropertyAnimation(messageLabel, "geometry");
    animation->setDuration(150);
    animation->setStartValue(startPos);
    animation->setEndValue(endPos);

    animation->start();
}

void MainWindow::deleteItem()
{
    parser->deleteItem(lastSelected, curSelected[lastSelected]);
}

void MainWindow::networkError(int nErr)
{
    if(nErr == 3)
        showMessage(tr("Internet died..."));
    if(nErr == 203) {
        showMessage(tr("Link is outdated"));
        player->playNext();
    }
}

QPixmap MainWindow::queueIcon(int index)
{
    QPainter p;

    QPixmap *pm = new QPixmap(":/icons/current");

    p.begin(pm);
    p.setPen(Qt::white);
    p.setFont(QFont("Mono", 20, 100));
    p.drawText(pm->width()/2 - 11,pm->height()/2+8, QString::number(index));

    return *pm;
}

void MainWindow::addDownload()
{
    parser->addDownload(lastSelected, curSelected[lastSelected]);
    if(!isDPopupVis)
        showDPopup();
}

void MainWindow::showDPopup()
{
    //dBar->setGeometry(QRect());
    isDPopupVis = true;

    QRect startPos(downloadLabel->parentWidget()->width() - 330, downloadLabel->parentWidget()->height(), 0, 0);
    QRect endPos(downloadLabel->parentWidget()->width() - 330, downloadLabel->parentWidget()->height() - 120, 0, 0);

    dBar->setGeometry(0, downloadLabel->height() - 30 , downloadLabel->width(), 10);

    downloadLabel->setHidden(false);

    QPropertyAnimation *animation = new QPropertyAnimation(downloadLabel, "geometry");
    animation->setDuration(150);
    animation->setStartValue(startPos);
    animation->setEndValue(endPos);
    animation->start();
}

void MainWindow::hideDPopup()
{
    isDPopupVis = false;

    QRect endPos(downloadLabel->parentWidget()->width() - 330, downloadLabel->parentWidget()->height(), 0, 0);
    QRect startPos(downloadLabel->parentWidget()->width() - 330, downloadLabel->parentWidget()->height() - 120, 0, 0);

    dBar->setGeometry(0, downloadLabel->height() - 30 , downloadLabel->width(), 10);

    QPropertyAnimation *animation = new QPropertyAnimation(downloadLabel, "geometry");
    animation->setDuration(200);
    animation->setStartValue(startPos);
    animation->setEndValue(endPos);
    animation->start();
    connect(animation, SIGNAL(finished()), downloadLabel, SLOT(hide()));
}

void MainWindow::setDownloadProgress(qint64 current, qint64 total)
{
    dBar->setMaximum(total);
    dBar->setValue(current);
}

void MainWindow::setDownloadView(int listIndex, int index, int queueCount)
{
    QString artist = parser->sources[listIndex][index]["artist"];
    QString title = parser->sources[listIndex][index]["title"];
    artist.truncate(50);
    title.truncate(50);
    dCurTitle->setText(artist + "<br>" + title);
    dQueue->setText(tr("In queue: ") + QString::number(queueCount));
}

void MainWindow::setDownloadQCount(int count)
{
    dQueue->setText("In queue: " + QString::number(count));
}

void MainWindow::allDownloaded()
{
    dQueue->setText(tr("Complete"));
    QTimer::singleShot(2000, this, SLOT(hideDPopup()));
}

void MainWindow::addToList()
{
    int tListIndex = sender()->property("lid").toInt();
    parser->sources[tListIndex].insert(parser->sources[tListIndex].size(),  parser->sources[lastSelected][curSelected[lastSelected]]);
    setupList(3);
    parser->savePlayList();
}

void MainWindow::s_Time(qint64 s)
{
    QTime n(0, 0, 0);
    QTime t;
    n = t.addMSecs(s);
    l_CTime->setText(n.toString("m:ss"));
}

void MainWindow::s_TotalTime(qint64 s)
{
    QTime n(0, 0, 0);
    QTime t;
    n = t.addMSecs(s);
    l_TTime->setText(n.toString("m:ss"));
}

void MainWindow::trayClick()
{
    if(isHidden())
        show();
    else
        hide();
}

void MainWindow::quitApp()
{
    destroy();
    QApplication::quit();
}

void MainWindow::resizeEvent(QResizeEvent *rEvent)
{
    updateWidgets();
}


void MainWindow::updateWidgets()
{
    if(mainTabs->width() > 100)
        quitButton->setGeometry(mainTabs->width() - 25, 0, quitButton->width(), quitButton->height());
}

void MainWindow::trayWheelUp()
{
    if(trayWheelTracks)
        player->playNext();
    else
        player->volumeUp();
}

void MainWindow::trayWheelDown()
{
    if(trayWheelTracks)
        player->playPrev();
    else
        player->volumeDown();
}

void MainWindow::showAbout()
{
    QString aboutStr = "<center>\
            <font style=\"font-weight: bold; font-size: 19px;\">VKPlayer</font><br>\
            "+version+"<br><br>\
            "+tr("Author")+"<br><b>Vasily 'yuberion' Kiniv</b><br><a href=\"mailto: yuberion@gmail.com\">yuberion@gmail.com</a><br><a href=\"http://twitter.com/yuberion\">@yuberion on Twitter</a><br><br>\
            "+tr("Designer")+"<br><b>Anatoliy Romanovich 'Elrond_Smith' Shapovalov </b><br><a href=\"mailto: elrond.716.smith@gmail.com\">elrond.716.smith@gmail.com</a><br><br>\
            "+tr("Translate to english")+"<br><b>"+tr("yuberion")+"</b><br><a href=\"mailto: "+tr("yuberion@gmail.com")+"\">"+tr("yuberion@gmail.com")+"</a><br><br>\
            "+tr("Website partner")+"<br><a style=\"font-weight: bold; font-size: 15px;\" href=\"http://ubuntovod.ru/\">ubuntovod.ru</a><br><br>\
            "+tr("Build for Windows and dbus communication for Linux")+"<br><b>VlaoMao</b><br><a href=\"mailto: "+tr("vlaomao@gmail.com")+"\">"+tr("vlaomao@gmail.com")+"</a>"\
            "</center>";
    QMessageBox::about(this, tr("About..."), aboutStr);
}

void MainWindow::setProps(QStringList strList, int index)
{
    propLists[index]->setProps(strList);
}

void MainWindow::propClicked(QString str)
{
    int index = sender()->parent()->property("lid").toInt();
   queryEdit[index]->setText(str);
  parser->doZaebis(index);
}

void MainWindow::copy2Clipboard()
{
    QString title = parser->sources[lastSelected][curSelected[lastSelected]]["artist"] +" - "+ parser->sources[lastSelected][curSelected[lastSelected]]["title"] ;

    QApplication::clipboard()->setText(title);
}
