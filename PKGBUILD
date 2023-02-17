# Maintainer: Devin J. Pohly <djpohly+arch@gmail.com>
pkgname=dwl-git
pkgver=0.4.r5.f8373cc
pkgrel=1
pkgdesc="Simple, hackable dynamic tiling Wayland compositor (dwm for Wayland)"
arch=('x86_64')
url="https://github.com/djpohly/dwl"
license=('GPL')
depends=('wlroots>=0.15')
makedepends=('git' 'wayland-protocols')
optdepends=('xorg-xwayland: for XWayland support')
provides=("${pkgname%-git}")
conflicts=("${pkgname%-git}")
# append #branch=wlroots-next to build against wlvroots-git
source=('git+https://github.com/djpohly/dwl'
	'autostart.patch::https://github.com/djpohly/dwl/compare/main...sevz17:autostart.patch'
	'shiftview.patch::https://github.com/djpohly/dwl/compare/main...guidocella:shiftview.patch'
	'swallow.patch::https://github.com/djpohly/dwl/compare/main...dm1tz:04-swallow.patch'
	'vanitygaps.patch::https://github.com/djpohly/dwl/compare/main...sevz17:vanitygaps.patch'
)

sha256sums=('SKIP'
            '342c6853baa44b80af712e0242d2931e6b66e3691fab73bfd4ce4b25c6ade3f6'
            'a6f3fcb440e3073799b8c1af83ff18cd9fd4c5809ebcfd8cff9bd5909ef35248'
            'ad47fb3c58ef15999ab9cbba4e72c517716b756578d1b361a4777cc458f80a08'
            'f2f37f49d05316c285b7cc0a059e3601b460427afd09f0d38c93e269cb8aeba9')

prepare() {
	cd "$srcdir/${pkgname%-git}"

	# Uncomment to compile with XWayland support
	sed -i -e '/-DXWAYLAND/s/^#//' config.mk
	sed -i -e '/xcb/s/^#//' config.mk

	patch -p1 -t --input "$srcdir/autostart.patch"
	# patch -p1 -t --input "$srcdir/swallow.patch"
	patch -p1 -t --input "$srcdir/vanitygaps.patch"
	patch -p1 -t --input "$BUILDDIR/squibidmoveKeyboard.patch"
	patch -p1 -t --input "$srcdir/shiftview.patch"

	# This package provides a mechanism to provide a custom config.h. Multiple
	# configuration states are determined by the presence of two files in
	# $BUILDDIR:
	#
	# config.h  config.def.h  state
	# ========  ============  =====
	# absent    absent        Initial state. The user receives a message on how
	#                         to configure this package.
	# absent    present       The user was previously made aware of the
	#                         configuration options and has not made any
	#                         configuration changes. The package is built using
	#                         default values.
	# present                 The user has supplied his or her configuration. The
	#                         file will be copied to $srcdir and used during
	#                         build.
	#
	# After this test, config.def.h is copied from $srcdir to $BUILDDIR to
	# provide an up to date template for the user.
	if [ -e "$BUILDDIR/config.h" ]; then
		cp "$BUILDDIR/config.h" .
	elif [ ! -e "$BUILDDIR/config.def.h" ]; then
		msg='This package can be configured in config.h. Copy the config.def.h '
		msg+='that was just placed into the package directory to config.h and '
		msg+='modify it to change the configuration. Or just leave it alone to '
		msg+='continue to use default values.'
		echo "$msg"
	fi
	cp config.def.h "$BUILDDIR"
}

pkgver() {
	cd "$srcdir/${pkgname%-git}"
	printf "%s" "$(git describe --long | sed 's/^v//;s/\([^-]*-\)g/r\1/;s/-/./g')"
}

build() {
	cd "$srcdir/${pkgname%-git}"
	make
}

package() {
	cd "$srcdir/${pkgname%-git}"
	make PREFIX="$pkgdir/usr/" install
}
