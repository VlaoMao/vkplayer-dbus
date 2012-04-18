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
     Q_PROPERTY(bool shuffle READ isShuffle WRITE setShuffle)
     Q_PROPERTY(bool repeat READ isRepeat() WRITE setRepeat)

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
                    player->playPause(true);
                    //player->playIndex(2);
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
     Q_INVOKABLE void VolumeDown()
         {
             player->volumeDown();
         }
     Q_INVOKABLE void VolumeUp()
         {
             player->volumeUp();
         }
     Q_INVOKABLE void setShuffle(bool isShuffle)
         {
             player->setShuffle(isShuffle);
         }
     Q_INVOKABLE bool isShuffle()
         {
             return player->isShuffle();
         }
     Q_INVOKABLE void setRepeat(bool isRepeat)
         {
             player->setRepeat(isRepeat);
         }
     Q_INVOKABLE bool isRepeat()
         {
             return player->isRepeat();
         }
     Q_INVOKABLE void mute()
         {
             player->Mute();
         }
     Q_INVOKABLE void unmute()
         {
             player->UnMute();
         }

     void SetPlayerPointer(Player* aNewPointer);

private:
    Player* player;
 };
#endif // DBUS_H
