#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    qDebug() << translator.load("/usr/share/vkplayer/translations/vkplayer_" + QLocale::system().name());

    QCoreApplication::setAttribute(Qt::AA_DontShowIconsInMenus, false);

    a.installTranslator(&translator);

    a.setApplicationName( "VKPlayer" );
    MainWindow w;
    w.show();

    return a.exec();
}
