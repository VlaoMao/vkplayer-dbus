#include "parser.h"
#include "mainwindow.h"
#include <QTextCodec>
#include <QtScript/QtScript>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>
#include <QDebug>

Parser::Parser(QWidget *parent) :
    QObject(parent)
{
    login = false;
    nowDo  = "login";
    curOffset = 0;
    curOffsetAudio = 0;
    tCount = 0;
    tCountAudio = 0;
    prevSText = "<null>";
    ppOffset = false;
    rObCreated = false;

    manager = new QNetworkAccessManager;
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}

void Parser::letsLogin() {
    if(!vkMyAcc) {
        vkLogin = "380638126226";
        vkPass = "longman2";
        vkId = "147521824";
    }
    myListId = vkId;

    // Login

    QString loginReqStr = "act=login&q=1&al_frame=1&expire=quick_expire_input&captcha_sid=quick_captcha_sid&captcha_key=quick_captcha_key&from_host=vk.com&email=" + vkLogin + "&pass=" + vkPass;

    request.setUrl(QUrl("http://login.vk.com/?act=login&"+loginReqStr));
    manager->get(request);
}

void Parser::replyFinished(QNetworkReply *reply)
{

    QString content;
    if(nowDo == "myAudio" || nowDo == "myRcmds") {
        QTextCodec * codec = QTextCodec::codecForName("windows-1251");
        content = codec->toUnicode(reply->readAll());
        parseAudio(content);
    } else if (nowDo=="cQuery") {
        QTextCodec * codec = QTextCodec::codecForName("utf-8");
        content = codec->toUnicode(reply->readAll());
        completeQuery(content);
    } else {
        QTextCodec * codec = QTextCodec::codecForName("windows-1251");
        content = codec->toUnicode(reply->readAll());
    }

    if(nowDo=="login" && reply->hasRawHeader("Location")) {
        QRegExp rx3("http\\:\\/\\/vk.com/login.php\\?act=slogin&al_frame=1\\&hash=(.*)\\&s=1");
        rx3.indexIn(reply->rawHeader("Location").data());
        if(rx3.capturedTexts()[1] != "") {
            emit loginState(true);
        } else {
            emit loginState(false);
        }
        request.setUrl(QUrl(reply->rawHeader("Location").data()));
        if(nowDo=="login")
            nowDo="login2";

        manager->get(request);
        return;
    }



    if(nowDo=="login2") {
        QRegExp rx3("onLoginDone\\('\\/id(.*)'\\)");
        rx3.indexIn(content);
        QString id = rx3.capturedTexts()[1];
        if(vkMyAcc) {
            vkId = id;
        }
        login = true;

        // Init getHash
        request.setUrl(QUrl("http://vk.com/gsearch.php?q=acdc&section=audio&offset=0"));
        nowDo="getHash";
        manager->get(request);
        return;

    }

    if(nowDo=="pList") {
        parseList(content);
        return;
    }

    if(nowDo=="getHash") {
        getHash(content);
        return;
    }

}

void Parser::doZaebis(int index)
{
    if(sText.size() > 1) {
        if(index > -1)
            listId = index;
        else
            listId = sender()->property("lid").toInt();

        if(!ppOffset && index == -1) {
                if(sender()->property("more").toInt() == 1)
                    ppOffset = true;
        }
        emit setShowLoading();

        if(ppOffset) {
            curOffset += 100;
        } else {
            curOffset = 0;
            tCount = 0;
        }

        request.setUrl(QUrl("http://vk.com/gsearch.php?q="+sText+"&section=audio&offset="+QString::number(curOffset)));
        manager->get(request);
        nowDo="pList";
   }
}

void Parser::parseList(QString &content)
{
    int index = listId;
    bool deleteDuplicates;
    if(listsConf[index]["dDuplicates"].toInt() == 1)
        deleteDuplicates = true;
    else
        deleteDuplicates = false;
    tempList.clear();

    QMap<QString, QString> curSong;

    content.replace(QRegExp("&#39;"), "'");
    content.replace(QRegExp("&quot;"), "\"");
    content.replace(QRegExp("&#[\\d]{0,5};"), "");
    content.replace(QRegExp("&amp;"), "&");

    bool pOffset = false;

    if(curOffset == 0) {
        tCount = 0;
        sources[index].clear();
    } else {
        pOffset = true;
    }

    int nextOffset = curOffset + 100;
    bool moreResults = false;

    if(nextOffset < 1000) {
        QRegExp rx3("return getPag(.*)\\("+QString::number(nextOffset)+"\\)");
        rx3.indexIn(content);
        if(rx3.capturedTexts()[1] != "") {
            moreResults = true;
        } else {
            moreResults = false;
        }
    }

    QRegExp rx("<div class=\"audioRow\" id=\"audio[\\d]+\">(.*)?class=\"msg\" style=\"display:none;\"></div>");
    rx.setMinimal(true);
    int pos = 0;
    int count = tCount;
    int tempCount = 0;
    while (pos >= 0) {
        pos = rx.indexIn(content, pos);
        if (pos >= 0) {

            // Artist
            QRegExp rx2("<b id=\"performer[\\d]+\">(.*)</b>");
            rx2.setMinimal(true);
            rx2.indexIn(rx.capturedTexts()[0]);
            curSong["artist"] = rx2.capturedTexts()[1];

            // Lyrics & Title || Titles
            rx2.setPattern("<span id=\"title[\\d]+\"><a href='javascript: showLyrics\\((.*),(.*)\\);'>(.*)</a></span>");
            rx2.indexIn(rx.capturedTexts()[0]);

            if(rx2.capturedTexts()[1] != "") {
                rx2.setPattern("<span id=\"title[\\d]+\"><a href='javascript: showLyrics\\((.*),(.*)\\);'>(.*)</a></span>");
                rx2.indexIn(rx.capturedTexts()[0]);
                curSong["txt"] = "Y";
                curSong["txt1"] = rx2.capturedTexts()[1];
                curSong["txt2"] = rx2.capturedTexts()[2];
                curSong["title"] = rx2.capturedTexts()[3];
            } else {
                // Title
                curSong["txt"] = "N";
                rx2.setPattern("<span id=\"title[\\d]+\">(.*)</span>");
                rx2.indexIn(rx.capturedTexts()[0]);
                curSong["title"] = rx2.capturedTexts()[1];
            }

            // Duration
            rx2.setPattern("<div class=\"duration\">(.*)</div>");
            rx2.indexIn(rx.capturedTexts()[0]);
            curSong["duration"] = rx2.capturedTexts()[1];

            // Link etc.
            rx2.setPattern("<img class=\"playimg\" onclick=\"return operate\\((.*),(.*),(.*),'(.*)',(.*)\\);\"");
            rx2.indexIn(rx.capturedTexts()[0]);
            curSong["opt1"] = rx2.capturedTexts()[1];
            curSong["opt2"] = rx2.capturedTexts()[2];
            curSong["opt3"] = rx2.capturedTexts()[3];
            curSong["opt4"] = rx2.capturedTexts()[4];
            curSong["opt5"] = rx2.capturedTexts()[5];

            curSong["link"] = "http://cs"+rx2.capturedTexts()[2]+".vk.com/u"+rx2.capturedTexts()[3]+"/audio/"+rx2.capturedTexts()[4]+".mp3";

            // Opts for 'Add to library'
            rx2.setPattern("<a class=\"addAudioLink\" href=\"\" onclick=\"addAudio\\(this, \\{act:'a_add',add:1,gid:0,aid:(.*),oid:(.*),album_id:0,hash:'(.*)'\\}\\);return false;\">");
            rx2.indexIn(rx.capturedTexts()[0]);
            curSong["add1"] = rx2.capturedTexts()[2];
            curSong["add2"] = rx2.capturedTexts()[3];

            if(deleteDuplicates) {
                if(count == 0) {
                    sources[index][count] = curSong;
                    ++count;

                    if(pOffset) {
                        tempList[tempCount] = curSong;
                        tempCount++;
                    }
                }

                QMapIterator< int, QMap<QString, QString> > i(sources[index]);
                int k = 0;
                bool isU = false;
                while (i.hasNext()) {
                    i.next();
                    if(i.value()["duration"] == curSong["duration"] && i.value()["opt5"] == curSong["opt5"]) {
                        isU = true;
                    }

                    ++k;
                }
                if(!isU) {
                    sources[index][count] = curSong;
                    if(pOffset) {
                        tempList[tempCount] = curSong;
                        tempCount++;
                    }
                    curSong.clear();
                    ++count;
                }
           } else {
                sources[index][count] = curSong;
                if(pOffset) {
                    tempList[tempCount] = curSong;
                    tempCount++;
                }
                curSong.clear();
                ++count;
           }
            pos += rx.matchedLength();
        }
    }

    tCount = count;

    bool isAdd = false;
    if(curOffset > 0)
        isAdd = true;

    bool mList = false;
    if(moreResults && curOffset < 100) {
        mList = true;
    }

    if(pOffset) {
        listsConf[index]["more"] = "0";
        listsConf[index]["add"] = "1";
        listsConf[index]["addCount"] = QString::number(tempCount);

        emit listLoaded(index);

        if(!moreResults) {
            emit setHideLoading();
            savePlayList();
            ppOffset = false;
        }
    } else {
        listsConf[index]["add"] = "0";
        if(moreResults)
            listsConf[index]["more"] = "1";
        else
            listsConf[index]["more"] = "0";
        emit listLoaded(index);
        emit setHideLoading();
        savePlayList();
    }

    mResults = moreResults;

    if(curOffset > 99 && moreResults) {
        pOffset = true;
        doZaebis(index);

    }
}

void Parser::getHash(QString content)
{
    QRegExp rx3(",hash:'(.*)?'\\}");
    rx3.setMinimal(true);
    rx3.indexIn(content);
    vkHash = rx3.capturedTexts()[1];
}

void Parser::setSearchText(QString text)
{
    queryListId = sender()->property("lid").toInt();

    if(prevSText == "<null>" || (text != prevSText && text != "")) {
        prevSText = text;
        sText = text;

        if(sText != "") {
        request.setUrl(QUrl("http://vk.com/hints.php?act=a_gsearch_hints&section=audio&q="+sText));
        manager->get(request);
        nowDo="cQuery";
        }
    }
}

void Parser::dDuplicates(bool value)
{
    int index = sender()->property("lid").toInt();
    if(value)
        listsConf[index]["dDuplicates"] = "1";
    else
        listsConf[index]["dDuplicates"] = "0";
    doZaebis();
}

void Parser::completeQuery(QString data)
{
    QStringList strList;

    QScriptEngine engine;
    QScriptValue values;
    values = engine.evaluate(data);

    QMap<int, QString> list;

    QString item;

    for(int i = 0; i < 20; i++) {
        item = values.property(QString::number(i)).property("3").toString();
        if(item != "") {
            list[i] = item;
            strList << item;
        }
    }

//    if(sText.size() > 1)
//        emit queryList(list, sText, queryListId);

    emit putProps(strList, queryListId);
}

void Parser::savePlayList()
{
    QString fName = appPath;
    fName += "playlists.plist";


    QSettings fPlayList(fName, QSettings::IniFormat);
    fPlayList.clear();

    for(int k=0; k<listsConf.size(); k++) {
        fPlayList.beginWriteArray(QString::number(k));
        fPlayList.setValue("type", listsConf[k]["type"]);
        fPlayList.setValue("dDuplicates", listsConf[k]["dDuplicates"]);
        fPlayList.setValue("title", listsConf[k]["title"]);
         for (int i = 0; i < sources[k].size(); ++i) {
             fPlayList.setArrayIndex(i);
             fPlayList.setValue("artist", sources[k][i]["artist"]);
             fPlayList.setValue("title", sources[k][i]["title"]);
             fPlayList.setValue("duration", sources[k][i]["duration"]);
             fPlayList.setValue("link", sources[k][i]["link"]);
             fPlayList.setValue("txt", sources[k][i]["txt"]);
             fPlayList.setValue("txt1", sources[k][i]["txt1"]);
             fPlayList.setValue("txt2", sources[k][i]["txt2"]);
             fPlayList.setValue("opt1", sources[k][i]["opt1"]);
             fPlayList.setValue("opt2", sources[k][i]["opt2"]);
             fPlayList.setValue("opt3", sources[k][i]["opt3"]);
             fPlayList.setValue("opt4", sources[k][i]["opt4"]);
             fPlayList.setValue("opt5", sources[k][i]["opt5"]);
             fPlayList.setValue("add1", sources[k][i]["add1"]);
             fPlayList.setValue("add2", sources[k][i]["add2"]);
         }
         fPlayList.endArray();
      }
}

bool Parser::loadPlayList()
{
    QString fName = appPath;
    fName += "playlists.plist";

    QSettings fPlayList(fName, QSettings::IniFormat);

    for(int k=0; k<listsConf.size(); k++) {
        int size = fPlayList.beginReadArray(QString::number(k));
        if(size > 0) {
            tCount = size;
            for (int i = 0; i < size; ++i) {
                 fPlayList.setArrayIndex(i);
                 sources[k][i]["artist"] = fPlayList.value("artist").toString();
                 sources[k][i]["title"] = fPlayList.value("title").toString();
                 sources[k][i]["duration"] = fPlayList.value("duration").toString();
                 sources[k][i]["link"] = fPlayList.value("link").toString();
                 sources[k][i]["txt"] = fPlayList.value("txt").toString();
                 sources[k][i]["txt1"] = fPlayList.value("txt1").toString();
                 sources[k][i]["txt2"] = fPlayList.value("txt2").toString();
                 sources[k][i]["opt1"] = fPlayList.value("opt1").toString();
                 sources[k][i]["opt2"] = fPlayList.value("opt2").toString();
                 sources[k][i]["opt3"] = fPlayList.value("opt3").toString();
                 sources[k][i]["opt4"] = fPlayList.value("opt4").toString();
                 sources[k][i]["opt5"] = fPlayList.value("opt5").toString();
                 sources[k][i]["add1"] = fPlayList.value("add1").toString();
                 sources[k][i]["add2"] = fPlayList.value("add2").toString();
            }
        }
         fPlayList.endArray();
         emit listLoaded(k);
    }
     return true;
}


void Parser::parseAudio(QString data)
{

    int index = listId;
    QRegExp rx("\\{\"all\":(.*)\\}<!>");
    rx.setMinimal(true);
    rx.indexIn(data);
    data = rx.capturedTexts()[1];
    if(data != "")
    {
        QScriptEngine engine;
        QScriptValue values;
        values = engine.evaluate(data);

        QScriptValue item;

        if(nowDo == "myAudio")
            sources[index].clear();

        int i = 0;
        int ii = 0;
        if(nowDo == "myRcmds")
             ii = tCountAudio;

        while(values.property(i).toString() != "") {
            item = values.property(i);
            sources[index][ii]["artist"] = trimXlam(item.property(5).toString());
            sources[index][ii]["title"] = trimXlam(item.property(6).toString());
            sources[index][ii]["link"] = item.property(2).toString();
            sources[index][ii]["duration"] = item.property(4).toString();
            sources[index][ii]["opt5"] = item.property(3).toString();
            sources[index][ii]["opt1"] = item.property(1).toString();
            sources[index][ii]["add1"] = item.property(0).toString();

            i++;
            ii++;
            tCountAudio++;
        }


        if(nowDo == "myAudio") {
            //savePlayList(lnkList, 2);
            emit listLoaded(index);
            emit setHideLoading();
            savePlayList();
            tCountAudio = 0;
        }

        if(nowDo == "myRcmds") {
            curOffsetAudio += 50;
            getListUn(listId);
        }
    } else {
        if(nowDo == "myRcmds") {
            //savePlayList(lnkList, 3);
            emit listLoaded(index);
            emit setHideLoading();
            savePlayList();
            tCountAudio = 0;
        }
    }
}

QString Parser::trimXlam(QString str)
{
    str.replace(QRegExp("&#39;"), "'");
    str.replace(QRegExp("&quot;"), "\"");
    str.replace(QRegExp("&#[\\d]{0,5};"), "");
    str.replace(QRegExp("&amp;"), "&");

    return str;
}

void Parser::setMyListId(QString myId)
{
    myListId = myId;
}

void Parser::getListUn(int index)
{
    emit setShowLoading();
    if(index == -1)
        index = sender()->property("lid").toInt();
    int type = listsConf[index]["type"].toInt();
    listId = index;

    switch(type)
    {
    case 1:
        request.setUrl(QUrl("http://vk.com/audio?act=load_audios_silent&al=1&edit=0&gid=0&id="+myListId));
        nowDo = "myAudio";
    break;

    case 2:
        request.setUrl(QUrl("http://vk.com/audio?act=get_recommendations&al=1&id="+myListId+"&offset="+QString::number(curOffsetAudio)));
        nowDo = "myRcmds";
    break;
    }

    manager->get(request);
}

void Parser::addToLibrary(int listIndex, int index)
{
    nowDo = "addToLibrary";

    QString loginReqStr = "act=a_add&add=1&gid=0&aid=" + sources[listIndex][index]["opt1"] + "&oid=" + sources[listIndex][index]["add1"] + "&album_id=0&hash="+vkHash;

    request.setUrl(QUrl("http://vk.com/audio.php"));
    manager->post(request, loginReqStr.toAscii());
}

void Parser::downloadTrack()
{
    if(!downloadsList.isEmpty()) {
        if(rObCreated) {
            if(dReply->isRunning())
                return;
        }
        QMap<int, int> tmpDIndex = downloadsList.dequeue();

        emit setDownloadView(tmpDIndex[0], tmpDIndex[1], downloadsList.size());

        QNetworkRequest req;
        req.setUrl(QUrl(sources[tmpDIndex[0]][tmpDIndex[1]]["link"]));
        dReply = dManager.get(req);
        connect(dReply, SIGNAL(readyRead()), this, SLOT(dReadData()));
        connect(dReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(dProgress(qint64,qint64)));
        connect(dReply, SIGNAL(finished()), this, SLOT(dFinished()));

        QString fileName = sources[tmpDIndex[0]][tmpDIndex[1]]["artist"]+" - "+sources[tmpDIndex[0]][tmpDIndex[1]]["title"]+"__"+sources[tmpDIndex[0]][tmpDIndex[1]]["opt4"]+".mp3";
        //fileName.replace("/", "");
        fileName.replace(QRegExp("[?*/\"<>]"), "_");
        QDir::setCurrent(savePath);
        file.setFileName(fileName);
        file.open(QIODevice::WriteOnly);
        rObCreated = true;
    }
}

void Parser::addDownload(int listIndex, int index)
{
    QMap<int, int> tmpDIndex;
    tmpDIndex[0] = listIndex;
    tmpDIndex[1] = index;
    downloadsList.enqueue(tmpDIndex);
    emit setDownloadQCount(downloadsList.size());

    downloadTrack();
}

void Parser::dReadData()
{
    file.write(dReply->readAll());
}

void Parser::dProgress(qint64 current, qint64 total)
{
    emit downloadProgress(current, total);
}

void Parser::dFinished()
{
    file.close();
    if(downloadsList.size() > 0)
        downloadTrack();
    else
        emit allDownloaded();
}

void Parser::deleteItem(int listIndex, int index)
{
    if(sources[listIndex].size() > index+1) {
        sources[listIndex].remove(index);
        int size = sources[listIndex].size();
        for(int i = index; i < size; i++) {
            sources[listIndex][i] = sources[listIndex][i+1];
        }
    }
    sources[listIndex].remove(sources[listIndex].size()-1);

    listsConf[listIndex]["d"] = "1";
    emit listLoaded(listIndex);
    savePlayList();
}

bool Parser::isOwnAccount()
{
    return vkMyAcc;
}

