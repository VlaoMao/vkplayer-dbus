#ifndef PLAYER_H
#define PLAYER_H

#include <phonon/AudioOutput>
#include <phonon/MediaObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QBuffer>
#include <QQueue>
#include <parser.h>

class Player : public QObject
{
    Q_OBJECT

public:
    Player();
    QMap< int, QMap<QString, QString> > playList;

    void playIndex(int, int listIndex = -1);

    enum State {
             STOPED = 0x0,
             PLAY = 0x1,
             PAUSED = 0x2,
             FINISHED = 0x4
    };
    Q_DECLARE_FLAGS(States, State)
    Player::States curState;

    bool listSync;
    int prevIndex;
    int curIndex;
    Phonon::MediaObject *mediaObject;
    Phonon::AudioOutput *audioOutput;
    int queueSize;
    QString currentList;
    int currentListIndex;
    Parser *parser;
    QString savePath;
    void setBufferOff(bool);
    bool isBufferOff();
    void volumeUp();
    void volumeDown();
    void Mute();
    void UnMute();
    Player::States getState(){return curState;}
private:
    void setState(Player::States);
    bool autoNext;
    double volLevel;
    QNetworkAccessManager nManager;
    QNetworkReply *nReply;
    QBuffer *buffer;
    bool canPlay;
    bool test2;
    qint64 cLenght;
    qint64 lastPos;
    QByteArray *ba;
    int blockNum;
    bool obCreated;
    bool ob2Created;
    bool sMusic;
    int queueList[100];
    QQueue<QMap<int, int> > qList;
    int duration;

    bool shuffle;
    bool repeat;

    QMap<int, int> getQeueu();
    void saveTrack();

    bool bufferOff;

    // KILLME
    qint64 tmpTotal;


public slots:
    void setList(QMap< int, QMap<QString, QString> >);
    void playPause(bool);
    void playNext();
    void playPrev();
    void setSaveMusic(bool);
    void cron();
    void addToQueue(int, int);
    void setShuffle(bool);
    bool isShuffle();
    void setRepeat(bool);
    bool isRepeat();
    void nError(QNetworkReply::NetworkError);

private slots:
    void playFinished();
    void readData();
    void rFinished();
    void dProgress(qint64,qint64);

signals:
    void stateChanged();
    void curSong(QMap<QString, QString>, int, bool);
    void bufferProgress(int, int);
    void playSomething();
    void setQueueView(int, int, int);
    void networkError(int);
    void tick(qint64);
    void totalTimeChanged(qint64);
    void play();
    void pause();
    void shuffleToggled(bool);
    void repeatToggled(bool);
    void muted(bool);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Player::States)

#endif // PLAYER_H
