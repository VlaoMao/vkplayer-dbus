#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent)
{
    setupUi();

     g_needRestart = false;
}

void SettingsWindow::setupUi()
{
    // Window seetins
    setWindowTitle(tr("Settings"));
    setWindowIcon(QIcon(QPixmap(":/icons/settings")));
    setWindowFlags(Qt::WindowTitleHint);
    setWindowOpacity(1);


    // Account group
    loginGroup = new QGroupBox(tr("VK Account"));
    myAccountCheckbox = new QCheckBox(tr("Use My Account"));

    QLabel *loginLabel = new QLabel(tr("Login"));
    QLabel *passLabel = new QLabel(tr("Password"));

    loginEdit = new QLineEdit("example@gmail.com");
    passEdit = new QLineEdit("", loginGroup);

    QVBoxLayout *loginLayout = new QVBoxLayout();
    loginLayout->addWidget(myAccountCheckbox);
    loginLayout->addWidget(loginLabel);
    loginLayout->addWidget(loginEdit);
    loginLayout->addWidget(passLabel);
    loginLayout->addWidget(passEdit);

    loginLayout->addStretch(1);

    loginGroup->setLayout(loginLayout);

    // App group
    appGroup = new QGroupBox(tr("Application settings"));

    QGridLayout *topAppLayout = new QGridLayout();

    em_Path = new QLineEdit(appPath+"/music");
    lm_Path = new QLabel(tr("Music save path"));
    bm_setPath = new QPushButton(tr("Choose"));
    connect(bm_setPath, SIGNAL(clicked()), SLOT(setPath()));
    topAppLayout->addWidget(lm_Path, 0, 0);
    topAppLayout->addWidget(em_Path, 1, 0);
    topAppLayout->addWidget(bm_setPath, 1, 1);

    cm_BufferOff = new QCheckBox(tr("Turn off buffering mode"));
    topAppLayout->addWidget(cm_BufferOff, 2, 0);

    close2TrayCheckbox = new QCheckBox(tr("Minimize to tray on close"));
    topAppLayout->addWidget(close2TrayCheckbox, 3, 0);

    cm_NotifyDisable = new QCheckBox(tr("Turn off notifications"));
    topAppLayout->addWidget(cm_NotifyDisable, 4, 0);

    QGroupBox *wheelActGroup = new QGroupBox(tr("Tray icon mouse-wheel action"));
    trayVolumeRadio = new QRadioButton(tr("Change volume"));
    trayVolumeRadio->setChecked(true);
    trayTrackRadio = new QRadioButton(tr("Change track"));

    QVBoxLayout *wheelActLayout = new QVBoxLayout();
    wheelActLayout->addWidget(trayVolumeRadio);
    wheelActLayout->addWidget(trayTrackRadio);
    wheelActGroup->setLayout(wheelActLayout);

    topAppLayout->addWidget(wheelActGroup, 5, 0, 2, 0);

    topAppLayout->setAlignment(Qt::AlignTop);

    QVBoxLayout *appLayout = new QVBoxLayout();
    appLayout->addLayout(topAppLayout);

    appGroup->setLayout(appLayout);

    // Bottom layout
    QHBoxLayout *bottomLayout = new QHBoxLayout();

    cancelButton = new QPushButton(tr("Cancel"));
    okButton = new QPushButton(tr("OK"));
    bottomLayout->addWidget(cancelButton, 0, Qt::AlignLeft);
    bottomLayout->addWidget(okButton, 1, Qt::AlignRight);

    // Set main layout
    QGridLayout *mainLayout = new QGridLayout();

    mainLayout->addWidget(loginGroup, 0, 0);
    mainLayout->addWidget(appGroup, 0, 1);
    mainLayout->addLayout(bottomLayout, 1, 1);

    setLayout(mainLayout);

    // Widget settings
    passEdit->setEchoMode(QLineEdit::Password);

    loginLabel->setEnabled(false);
    loginEdit->setEnabled(false);
    connect(loginEdit, SIGNAL(editingFinished()), this, SLOT(setNeedRestart()));

    passLabel->setEnabled(false);
    passEdit->setEnabled(false);
    connect(passEdit, SIGNAL(editingFinished()), this, SLOT(setNeedRestart()));

    // Tab orders
    setTabOrder(loginEdit, passEdit);

    // Gui connectios
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(saveSettings()));
    connect(myAccountCheckbox, SIGNAL(clicked(bool)), this, SIGNAL(myAccount(bool)));
    connect(myAccountCheckbox, SIGNAL(clicked()), this, SLOT(setNeedRestart()));
    connect(this, SIGNAL(myAccount(bool)), myAccountCheckbox, SLOT(setChecked(bool)));
    connect(this, SIGNAL(myAccount(bool)), loginLabel, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(myAccount(bool)), loginEdit, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(myAccount(bool)), passLabel, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(myAccount(bool)), passEdit, SLOT(setEnabled(bool)));
}

SettingsWindow::~SettingsWindow() {

}

void SettingsWindow::saveSettings()
{
    QSettings settings(appPath+"settings.ini", QSettings::IniFormat);

    int wAction;
    if(trayVolumeRadio->isChecked())
        wAction = 1;
    if(trayTrackRadio->isChecked())
        wAction = 2;

    settings.beginGroup("settingsw");
    settings.setValue("acc/myacc", myAccountCheckbox->isChecked());
    settings.setValue("acc/login", loginEdit->text());
    settings.setValue("acc/pass", passEdit->text());
    settings.setValue("app/savePath", em_Path->text());
    settings.setValue("app/bufferOff", cm_BufferOff->isChecked());
    settings.setValue("app/close2Tray", close2TrayCheckbox->isChecked());
    settings.setValue("app/wheelAction", wAction);
    settings.setValue("app/notifyDisable", cm_NotifyDisable->isChecked());
    settings.endGroup();

    emit settingsChange();

    if(g_needRestart)
        QMessageBox::information(this, tr("o.O"), tr("Restart application for apply changes."));

    close();
}

void SettingsWindow::loadSettings()
{
    QSettings settings(appPath+"settings.ini", QSettings::IniFormat);

    settings.beginGroup("settingsw");
    emit myAccount(settings.value("acc/myacc").toBool());
    loginEdit->setText(settings.value("acc/login").toString());
    passEdit->setText(settings.value("acc/pass").toString());
    em_Path->setText(settings.value("app/savePath").toString());
    cm_BufferOff->setChecked(settings.value("app/bufferOff").toBool());
    close2TrayCheckbox->setChecked(settings.value("app/close2Tray").toBool());
    cm_NotifyDisable->setChecked(settings.value("app/notifyDisable").toBool());

    int wAction;
    wAction = settings.value("app/wheelAction").toInt();
    if(wAction == 1)
        trayVolumeRadio->setChecked(true);
    if(wAction == 2)
        trayTrackRadio->setChecked(true);


    settings.endGroup();
}

void SettingsWindow::setPath()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Directory"), em_Path->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(dir != "")
        em_Path->setText(dir);
}

void SettingsWindow::setNeedRestart()
{
    g_needRestart = true;
}
