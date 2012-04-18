#-------------------------------------------------
#
# Project created by QtCreator 2011-05-02T07:14:08
#
#-------------------------------------------------

QT       += core gui network phonon script dbus

TARGET = vkplayer
TEMPLATE = app

include(translations/translations.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    parser.cpp \
    player.cpp \
    playlist.cpp \
    settingswindow.cpp \
    tray.cpp \
    proplist.cpp \
    dbus.cpp

HEADERS  += mainwindow.h \
    parser.h \
    player.h \
    playlist.h \
    settingswindow.h \
    tray.h \
    proplist.h \
    dbus.h

FORMS    +=

RESOURCES += \
    res.qrc

unix {
  #VARIABLES
  isEmpty(PREFIX) {
    PREFIX = /usr
  }
  BINDIR = $$PREFIX/bin
  DATADIR =$$PREFIX/share
  SHAREDIR =$$DATADIR/$${TARGET}

  DEFINES += DATADIR=\\\"$$DATADIR\\\" PKGDATADIR=\\\"$$PKGDATADIR\\\"

  #MAKE INSTALL

  INSTALLS += target translations desktop service icon16 icon22 icon24 icon32 icon48 icon64 icon96 icon128 iconsvg

  target.path =$$BINDIR

  translations.path = $$SHAREDIR
  translations.files += ../builddir/src/translations

  desktop.path = $$DATADIR/applications
  desktop.files += $${TARGET}.desktop

  service.path = $$DATADIR/dbus-1/services
  service.files += $${TARGET}.service

  icon16.path = $$DATADIR/icons/hicolor/16x16/apps
  icon16.files += data/16x16/$${TARGET}.png

  icon22.path = $$DATADIR/icons/hicolor/22x22/apps
  icon22.files += data/22x22/$${TARGET}.png

  icon24.path = $$DATADIR/icons/hicolor/24x24/apps
  icon24.files += data/24x24/$${TARGET}.png

  icon32.path = $$DATADIR/icons/hicolor/32x32/apps
  icon32.files += data/32x32/$${TARGET}.png

  icon48.path = $$DATADIR/icons/hicolor/48x48/apps
  icon48.files += data/48x48/$${TARGET}.png

  icon64.path = $$DATADIR/icons/hicolor/64x64/apps
  icon64.files += data/64x64/$${TARGET}.png

  icon96.path = $$DATADIR/icons/hicolor/96x96/apps
  icon96.files += data/96x96/$${TARGET}.png

  icon128.path = $$DATADIR/icons/hicolor/128x128/apps
  icon128.files += data/128x128/$${TARGET}.png

  iconsvg.path = $$DATADIR/icons/hicolor/scalable/apps
  iconsvg.files += data/scalable/$${TARGET}.svg

}
