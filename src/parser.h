#ifndef PARSER_H
#define PARSER_H
#include <QtNetwork>
#include <QMap>

class Parser : public QObject
{
    Q_OBJECT
private:
    // Download manager
    QNetworkAccessManager dManager;
    QNetworkReply *dReply;

    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QNetworkCookieJar *jarcookies;
    QMap< int, QMap<QString, QString> > tempList;
    bool login;
    QString nowDo;
    int curOffset;
    int curOffsetAudio;
    void completeQuery(QString);
    QString prevSText;
    void parseAudio(QString);
    QString trimXlam(QString);
    QString vkHash;
    void getList(int);
    void getHash(QString);

    // Download manager
    QQueue<QMap<int, int> > downloadsList;
    bool rObCreated;
    QFile file;

public:
    Parser(QWidget *parent = 0);
    void letsLogin();
    //QMap<int, QMap<int, QMap<QString, QString> > > lists;
    void parseList(QString &);
    void savePlayList();
    bool loadPlayList();
    QString sText;
    bool mResults;
    int tCount;
    int tCountAudio;
    QString appPath;
    QString myListId;
    void setMyListId(QString);
    //New lists
    QMap<int, QMap<int, QMap<QString, QString> > > sources;
    QMap<int, QMap<QString, QString> > listsConf;
    int listId;
    int queryListId;
    bool ppOffset;
    bool vkMyAcc;
    QString vkLogin;
    QString vkPass;
    QString vkId;
    QString savePath;

    void deleteItem(int, int);
    bool isOwnAccount();

    // Download manager
    void downloadTrack();

private slots:
    void replyFinished(QNetworkReply*);
    void dReadData();
    void dProgress(qint64,qint64);
    void dFinished();

public slots:
    void doZaebis(int index = -1);
    void setSearchText(QString);
    void dDuplicates(bool);
    // New lists
    void getListUn(int index = -1);
    void addToLibrary(int, int);
    void addDownload(int, int);

signals:
    void putContent(QString);
    void loginState(bool);
    void queryList(QMap<int, QString>, QString, int);
    void putProps(QStringList, int);//FIXME
    void setShowLoading();
    void setHideLoading();
    void listLoaded(int);

    void downloadProgress(qint64,qint64);
    void setDownloadView(int, int, int);
    void setDownloadQCount(int);
    void allDownloaded();
};

#endif // PARSER_H

