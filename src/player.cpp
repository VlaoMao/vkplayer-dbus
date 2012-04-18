#include "player.h"
#include <QNetworkReply>
#include <QFile>
#include <QDir>


Player::Player()
{
    curIndex = -1;
    prevIndex = -1;
    listSync = false;
    setState(Player::STOPED);
    autoNext = false;
    obCreated = false;
    sMusic = false;
    queueSize = -1;

    shuffle = false;
    repeat = false;

    bufferOff = false;

    mediaObject = new Phonon::MediaObject(this);
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(mediaObject, audioOutput);
    connect(mediaObject, SIGNAL(finished()), this, SLOT(playFinished()));
    connect(mediaObject, SIGNAL(tick(qint64)), this, SIGNAL(tick(qint64)));
    connect(mediaObject, SIGNAL(totalTimeChanged(qint64)), this, SIGNAL(totalTimeChanged(qint64)));

    ba = new QByteArray();
    buffer = new QBuffer();
}

void Player::playIndex(int index, int listIndex)
{
        qDebug() << "PlayIndex,index: " << index << "listIndex: " << listIndex;
    if(listIndex > -1) {
        if(currentListIndex != listIndex || !listSync) {
            setList(parser->sources[listIndex]);
            currentListIndex = listIndex;
        }
    }

    if(index > playList.size() - 1)
        index = 0;

    prevIndex = curIndex;
    curIndex = index;

    mediaObject->stop();
    setState(Player::STOPED);

    buffer->close();
    buffer->setData("");
    buffer = new QBuffer(mediaObject);


    QFile file;
    QDir::setCurrent(savePath);
    QString fileName = playList[curIndex]["artist"]+" - "+playList[curIndex]["title"]+"__"+playList[curIndex]["opt4"]+".mp3";
    fileName.replace(QRegExp("[?*/\"<>]"), "_");
    file.setFileName(fileName);
    if(file.open(QIODevice::ReadOnly)) {
        emit bufferProgress(1, 1);
        //buffer->setData(file.readAll());
        //buffer->open(QBuffer::ReadWrite);
        if(obCreated) {
            nReply->reset();
            if(nReply->isRunning())
                nReply->abort();
        }
        mediaObject->stop();
        mediaObject->setCurrentSource(Phonon::MediaSource(fileName));
        mediaObject->play();
        setState(Player::PLAY);
        ob2Created = true;
    } else {
        if(bufferOff)
        {
            emit bufferProgress(-1, -1);
            mediaObject->stop();
            mediaObject->setCurrentSource(Phonon::MediaSource(playList[curIndex]["link"]));
            mediaObject->play();
            setState(Player::PLAY);
        } else {
            blockNum = 0;

            QNetworkRequest req;
            req.setUrl(QUrl(playList[curIndex]["link"]));

            if(obCreated) {
                if(nReply->isRunning())
                    nReply->abort();
            }
            canPlay = false;
            nReply = nManager.get(req);
            connect(nReply, SIGNAL(readyRead()), this, SLOT(readData()));
            connect(nReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(dProgress(qint64,qint64)));
            connect(nReply, SIGNAL(finished()), this, SLOT(rFinished()));
            connect(nReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(nError(QNetworkReply::NetworkError)));
            obCreated = true;
        }

    }
    file.close();

    emit curSong(playList[curIndex], curIndex, autoNext);
    autoNext = false;

    QRegExp rx("(.*):(.*)"); // Сиськиии!)
    rx.indexIn(playList[curIndex]["duration"]);
    QString c1 = rx.capturedTexts()[1];
    QString c2 = rx.capturedTexts()[2];
    int dur1 = c1.toInt();
    int dur2 = c2.toInt();
    duration = dur1 * 60;
    duration += dur2;

}


void Player::setState(Player::States state)
{
    curState = state;
    emit stateChanged();
    if(state == Player::PLAY)
        emit play();
    else
        emit pause();
}

void Player::setList(QMap<int, QMap<QString, QString> > newList)
{
    prevIndex = -1;
    curIndex = -1;
    playList = newList;
    listSync = true;
}

void Player::playFinished()
{
    mediaObject->stop();
    setState(Player::FINISHED);
    autoNext = true;
    playNext();

}

void Player::playPause(bool state)
{
    if(state) {
        if(curState == Player::STOPED) {
            emit playSomething();
        } else {
            mediaObject->play();
            setState(Player::PLAY);
        }
    } else {
        mediaObject->pause();
        setState(Player::PAUSED);
    }

}

void Player::playNext()
{
    if(repeat && autoNext) {
        playIndex(curIndex);
    } else {
        QMap<int, int> q = getQeueu();
        if(q[1] > -1) {
            playIndex(q[1], q[0]);
        } else {
            if(shuffle) {
                playIndex(qrand() % playList.size());
            } else {
                playIndex(curIndex + 1);
            }
        }
    }
}

void Player::playPrev()
{
    playIndex(prevIndex);
}

void Player::readData()
{
    ++blockNum;

    qint64 blockSize = nReply->size();
    QByteArray data = nReply->readAll();

    if(cLenght > 0 && blockNum == 1) {
        ba->clear();
        lastPos = 0;

        ba = new QByteArray(cLenght, '\0');

        // I XLAM FIXME
//        QFile file;
//        QDir::setCurrent(savePath);
//        QString fileName = "pw.mp3";
//        file.setFileName(fileName);
//        file.open(QIODevice::ReadOnly);
//        file.seek(lastPos);
//        QByteArray tmpA = file.readAll();
//        qDebug() << tmpA.size();
//        lastPos = 6529943;
//        //ba = new QByteArray(cLenght, tmpA);
//        file.close();

//        ba = new QByteArray(tmpA);
    }

    ba->replace(lastPos, blockSize, data);
    data.clear();
    lastPos += blockSize;
}

void Player::rFinished()
{

}

void Player::dProgress(qint64 current, qint64 total)
{
    cLenght = total;

    int percent = 0;
    int playPercent = 0;
    if(total > 0 && current > 0) {
        percent = (current * 100 ) / total;
        int tPercent = (duration * 100 ) / 150;
        if(tPercent > 100) {
            playPercent = 2;
        } else {
            if(tPercent+40 < 100)
                playPercent = 102 - (tPercent+40);
            else
                playPercent = 2;
        }
    }

    if(percent > playPercent && !canPlay) {
        buffer->setBuffer(ba);
        buffer->open(QBuffer::ReadWrite);
        setState(Player::STOPED);
        mediaObject->stop();
        mediaObject->setCurrentSource(buffer);
        mediaObject->play();
        setState(Player::PLAY);
        canPlay = true;
    }
    emit bufferProgress(current, total);

    mediaObject->state();

    if(curState == Player::PLAY) {
        if(mediaObject->state() == 5) {
            mediaObject->setCurrentSource(buffer);
            mediaObject->play();
        }

        int tTotal = mediaObject->totalTime();
        int tCurrent = mediaObject->currentTime();
        if(tTotal > 1 && tCurrent > 1) {
            int tPercent = (tCurrent * 100 ) / tTotal;

            if((percent - tPercent) < 5) {
                mediaObject->pause();
            } else {
                if(mediaObject->state() != 2) {
                  mediaObject->play();
                }
            }
        }
    }

    if(current == total) {
       saveTrack();
    }
}

void Player::setSaveMusic(bool state)
{
    sMusic = state;
}

void Player::cron()
{
    if(curState == Player::PLAY && bufferOff) {
        if(mediaObject->state() != 2) {
            mediaObject->play();
        }
    }
}

void Player::addToQueue(int listIndex, int index)
{
    QMap<int, int> tmpQIndex;
    tmpQIndex[0] = listIndex;
    tmpQIndex[1] = index;
    qList.enqueue(tmpQIndex);
    queueSize++;
    emit setQueueView(listIndex, index, queueSize+1);
}

QMap<int, int> Player::getQeueu()
{
    if(!qList.isEmpty()) {
        queueSize--;
        for(int i=0; i<qList.size(); i++) {
            setQueueView(qList.at(i)[0], qList.at(i)[1], i);
        }
        return qList.dequeue();

    } else {
        QMap<int, int> tmpQueue;
        tmpQueue[0] = -1;
        tmpQueue[1] = -1;
        return tmpQueue;
    }
}

void Player::saveTrack()
{
    if(sMusic) {
        QString fileName = playList[curIndex]["artist"]+" - "+playList[curIndex]["title"]+"__"+playList[curIndex]["opt4"]+".mp3";
        fileName.replace(QRegExp("[?*/\"<>]"), "_");

        QFile file;
        QDir::setCurrent(savePath);
        file.setFileName(fileName);
        file.open(QIODevice::WriteOnly);
        file.write(buffer->data());
        file.close();
    }
}

void Player::setShuffle(bool state)
{
    shuffle = state;
    emit shuffleToggled(state);
}
bool Player::isShuffle()
    {
        return shuffle;
    }

void Player::setRepeat(bool state)
{
    repeat = state;
    emit repeatToggled(state);
}
bool Player::isRepeat()
    {
        return repeat;
    }

void Player::nError(QNetworkReply::NetworkError nErr)
{
    if(nErr != 5)
        qDebug() << "NETWORK_ERROR: " << nErr;
    emit networkError(nErr);
}

void Player::setBufferOff(bool state)
{
    bufferOff = state;
}

bool Player::isBufferOff()
{
    return bufferOff;
}

void Player::volumeUp()
{
    double cur = audioOutput->volume();
    if(cur <= 0.90)
        audioOutput->setVolume(cur + 0.10);
    if(cur >= 0.90)
        audioOutput->setVolume(1);
}

void Player::Mute()
    {
        volLevel = audioOutput->volume();
        audioOutput->setVolume(0);
        emit muted(true);
    }
void Player::UnMute()
    {
        audioOutput->setVolume(volLevel);
        emit muted(false);
    }

void Player::volumeDown()
{
    double cur = audioOutput->volume();
    if(cur >= 0.10)
        audioOutput->setVolume(cur - 0.10);
    if(cur <= 0.10)
        audioOutput->setVolume(0);
}
