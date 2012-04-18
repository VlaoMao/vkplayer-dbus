#ifndef TRAY_H
#define TRAY_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

class SysTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit SysTrayIcon(QObject *parent = 0) : QSystemTrayIcon(parent) {

    }

protected:
    virtual bool event(QEvent *e) {
        emit sEvent(e);
        return true;
    }

signals:
    void sEvent(QEvent *);
};

class Tray : public QObject
{
    Q_OBJECT
public:
    explicit Tray(QObject *parent = 0);

private:
    SysTrayIcon *trayIcon;
    QMenu *trayMenu;

    QAction *showWindow;
    QAction *pauseAction;
    QAction *nextAction;
    QAction *prevAction;
    QAction *quitAction;

    void createActions();
    void createIcon();


signals:
    void showW();
    void click();
    void pause();
    void next();
    void prev();
    void quit();

    void wheelUp();
    void wheelDown();

private slots:
    void trayClicked(QSystemTrayIcon::ActivationReason);
    void catchEvent(QEvent *);

public slots:
    void setPauseIcon();
    void setPlayIcon();

};

#endif // TRAY_H
