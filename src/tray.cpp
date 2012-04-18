#include "tray.h"
#include <QDebug>
#include <QEvent>
#include <QWheelEvent>

Tray::Tray(QObject *parent) :
    QObject(parent)
{
    createActions();
    createIcon();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), SLOT(trayClicked(QSystemTrayIcon::ActivationReason)));

    trayIcon->show();

}

void Tray::createActions()
{
    showWindow = new QAction(QIcon(QPixmap(":/icons/show")), tr("Show"), this);
    connect(showWindow, SIGNAL(triggered()), this, SIGNAL(click()));

    pauseAction = new QAction(QIcon(QPixmap(":/icons/big_pause")), tr("Pause"), this);
    connect(pauseAction, SIGNAL(triggered()), this, SIGNAL(pause()));

    nextAction = new QAction(QIcon(QPixmap(":/icons/next")), tr("Next"), this);
    connect(nextAction, SIGNAL(triggered()), this, SIGNAL(next()));

    prevAction = new QAction(QIcon(QPixmap(":/icons/prev")), tr("Prev"), this);
    connect(prevAction, SIGNAL(triggered()), this, SIGNAL(prev()));

    quitAction = new QAction(QIcon(QPixmap(":/icons/off")), tr("Quit"), this);
    connect(quitAction, SIGNAL(triggered()), this, SIGNAL(quit()));
}

void Tray::createIcon()
{
    // Create context menu
    trayMenu = new QMenu();
    trayMenu->addAction(showWindow);
    trayMenu->addSeparator();
    trayMenu->addAction(pauseAction);
    trayMenu->addAction(prevAction);
    trayMenu->addAction(nextAction);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAction);

    // Create tray icon object
    trayIcon = new SysTrayIcon(this);
    trayIcon->setContextMenu(trayMenu);
    connect(trayIcon, SIGNAL(sEvent(QEvent*)), SLOT(catchEvent(QEvent*)));
    setPauseIcon();
}

/* SLOTS */
void Tray::trayClicked(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger)
        emit click();

    if(reason == QSystemTrayIcon::MiddleClick)
        emit pause();
}

void Tray::catchEvent(QEvent *e)
{
    if(e->type() == QEvent::Wheel) {
        if(((QWheelEvent*)e)->delta() > 0)
            emit wheelUp();
        else
            emit wheelDown();
    } else {
        e->accept();
    }
}

void Tray::setPlayIcon()
{
    trayIcon->setIcon(QIcon(QPixmap(":/icons/trayPlay")));
}

void Tray::setPauseIcon()
{
    trayIcon->setIcon(QIcon(QPixmap(":/icons/trayPause")));
}
