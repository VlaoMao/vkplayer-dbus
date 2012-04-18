#include "proplist.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>

PropList::PropList(QWidget *parent) :
    QWidget(parent)
{
    setObjectName("propList");

    setMinimumHeight(0);

    setStyleSheet("QWidget#propList {border-radius: 10px; border-top-left-radius: 0px; border-top-right-radius: 0px; border-bottom: none; background-color: rgba(55, 55, 55, 210); color: #fff; font-size: 15px;}");

    QVBoxLayout *lay = new QVBoxLayout(this);

    list = new QListWidget(this);
    list->setFrameStyle(0);

    list->setStyleSheet("QListWidget {padding-bottom: 8px; border-radius: 10px; border-top-left-radius: 0px; border-top-right-radius: 0px; border-bottom: none; border-right: none; background-color: rgba(55, 55, 55, 0); color: #fff; font-size: 12px;} \
                         QListWidget::item {height: 15px;} \
                         QListWidget::item:selected {border: none;} \
                         QListWidget::item:hover {border-radius: 10px; border: none; background-color: rgba(0, 0, 0, 100);} \
                         QScrollBar:vertical {border: none; background-color: rgba(0, 0, 0, 0); width: 5px; } \
                         QScrollBar::handle:vertical {border: none; border-radius: 2px; background-color: #222; max-height: 3px;} \
                         QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {height: 0px; border: none;} \
                         QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {border: none;} \
                         QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background: none;} \
                       ");

    lay->addWidget(list);
    connect(list, SIGNAL(itemPressed(QListWidgetItem*)), SLOT(pClicked(QListWidgetItem*)));
    connect(list, SIGNAL(itemPressed(QListWidgetItem*)), SLOT(hideMe()));
    hide();
}

void PropList::paintEvent(QPaintEvent *)
 {
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
 }

void PropList::setDaddy(QLineEdit *edit)
{
    daddy = edit;
    connect(daddy, SIGNAL(editingFinished()), SLOT(hideMe()));
}

void PropList::setProps(QStringList strList)
{
    list->clear();
    list->addItems(strList);
    if(strList.size() > 0)
        showMe();
}

void PropList::pClicked(QListWidgetItem* index)
{
    emit activate(index->text());
}

void PropList::showMe()
{
    if(!isVisible()) {
        show();

        QRect startPos(daddy->pos().x()+7, (daddy->pos().y()+daddy->height() * 2), daddy->width()-7, 0);
        QRect endPos(daddy->pos().x()+7, (daddy->pos().y() + daddy->height()) * 2 - 5, daddy->width()-7, 100);

        QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
        animation->setDuration(150);
        animation->setStartValue(startPos);
        animation->setEndValue(endPos);
        animation->start();
    }
}

void PropList::hideMe()
{
    QRect endPos(daddy->pos().x()+7, (daddy->pos().y()+daddy->height() * 2 - 5), daddy->width()-7, 0);
    QRect startPos(daddy->pos().x()+7, (daddy->pos().y()+daddy->height() * 2), daddy->width()-7, 100);

    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(50);
    animation->setStartValue(startPos);
    animation->setEndValue(endPos);
    animation->start();
    connect(animation, SIGNAL(finished()), SLOT(hide()));
}
