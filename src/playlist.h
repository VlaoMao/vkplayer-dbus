#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QTreeView>

class playList : public QTreeView
{
    Q_OBJECT
public:
    explicit playList(QWidget *parent = 0);

private:
    virtual void keyPressEvent(QKeyEvent *event) {
        emit kEvent(event);
        QTreeView::keyPressEvent(event);
    }

signals:
    void kEvent(QKeyEvent *);

public slots:

};

#endif // PLAYLIST_H
