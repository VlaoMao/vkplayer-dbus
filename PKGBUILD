pkgname=vkplayer-dbus
pkgver=0.08.17
pkgrel=1
pkgdesc="VKPlayer Search music, load MyAudio and Recommendations playlists, save stream while"
arch=(any)
url="http://forum.ubuntu.ru/index.php?topic=168217"
license=('unknown')
depends=('qt' 'gstreamer0.10-ffmpeg' 'gstreamer0.10-ugly' 'gstreamer0.10-ugly-plugins' 'gstreamer0.10-good-plugins')
provides=('vkplayer')
conflicts=('vkplayer')
makedepends=('phonon')

build() {
  if [ -d ${srcdir}/${pkgname} ]; then
    pushd ${srcdir}/${pkgname}
    git pull origin
    popd
  else
    git clone git://github.com/VlaoMao/vkplayer-dbus.git
  fi
  cd "$srcdir/$pkgname/src"
  qmake
  patch Makefile -i ../../../make.patch 
  make
}

check() {
  cd "$srcdir/$pkgname/src"
  make -k check
}

package() {
  cd "$srcdir/$pkgname/src"
  make INSTALL_ROOT="${pkgdir}" install
}
