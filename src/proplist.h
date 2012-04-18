#ifndef PROPLIST_H
#define PROPLIST_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QModelIndex>

class PropList : public QWidget
{
    Q_OBJECT
public:
    explicit PropList(QWidget *parent = 0);
    void setDaddy(QLineEdit *);
    void setProps(QStringList);


private:
    QListWidget *list;
    QLineEdit *daddy;

    void setupUi();

protected:
    void paintEvent(QPaintEvent *);

signals:
    void activate(QString);

private slots:
    void pClicked(QListWidgetItem*);
    void hideMe();
    void showMe();
};

#endif // PROPLIST_H
