#ifndef DBUS_H
#define DBUS_H
#include <QApplication>
#include <QtCore>
#include <QtDBus>
#include "player.h"

class QCBAdapter: public QDBusAbstractAdaptor
 {
     Q_OBJECT
     Q_CLASSINFO("D-Bus Interface", "DBus.VKplayer.Player")
     //Q_PROPERTY(QString cbContent READ content WRITE setContent)

 private:
     QApplication *app;

 public:
     QCBAdapter(QApplication *application)
         : QDBusAbstractAdaptor(application)
     {

     }
     Q_INVOKABLE void PlayPause()
         {
             Player::States state = player->getState();
             if((state == Player::STOPED) || (state == Player::PAUSED))
                 {
                 //player->playPause(true);
                     player->playIndex(2);
                 }else{
                     player->playPause(false);
                 }
         }
     Q_INVOKABLE void PlayPrev()
         {
             player->playPrev();
         }
     Q_INVOKABLE void PlayNext()
         {
             player->playNext();
         }

     void SetPlayerPointer(Player* aNewPointer);
public slots:
    /* Q_NOREPLY void emptyClipboard()
     {
        cb->clear();
     }*/

private:
    Player* player;
 };
#endif // DBUS_H
