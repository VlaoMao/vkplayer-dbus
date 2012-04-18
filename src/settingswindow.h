#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QtGui>

class SettingsWindow : public QWidget
{
    Q_OBJECT
public:
    SettingsWindow(QWidget *parent = 0);
    ~SettingsWindow();

    QString appPath;
    void loadSettings();

private:
    // Ui
    QPushButton *okButton;
    QPushButton *cancelButton;

    QGroupBox *loginGroup;

    QCheckBox *myAccountCheckbox;
    QLineEdit *loginEdit;
    QLineEdit *passEdit;

    QGroupBox *appGroup;

    // Settoptions
    QLabel *lm_Path;
    QLineEdit *em_Path;
    QPushButton *bm_setPath;

    QCheckBox *cm_BufferOff;
    QCheckBox *close2TrayCheckbox;
    QCheckBox *cm_NotifyDisable;

    QRadioButton *trayVolumeRadio;
    QRadioButton *trayTrackRadio;

    // Misc
    bool g_needRestart;

    void setupUi();

private slots:
    void saveSettings();
    void setPath();
    void setNeedRestart();

signals:
    void myAccount(bool);
    void settingsChange();
};

#endif // SETTINGSWINDOW_H
