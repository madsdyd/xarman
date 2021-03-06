dnl ------------------------------------------------------------
dnl configure.in for xarman
dnl ------------------------------------------------------------

dnl CREDITS: Most of this stuff was stolen! Mostly from 
dnl tuxracer, but also some stuff from tuxkart and kde.


dnl ------------------------------------------------------------
dnl Setup initial stuff
dnl ------------------------------------------------------------
AC_INIT([xarman], [1.1.0])
AC_CONFIG_SRCDIR([src/xarman.cc])
AM_INIT_AUTOMAKE

dnl Enable --maintainer-mode
AM_MAINTAINER_MODE
dnl Put config.h in src
AM_CONFIG_HEADER(src/config.h)

dnl ------------------------------------------------------------
dnl Make sure all flags are blank
dnl ------------------------------------------------------------
CPPFLAGS=""
CXXFLAGS=""
LIBS=""


dnl ------------------------------------------------------------
dnl Check system type 
dnl ------------------------------------------------------------
dnl AC_CANONICAL_HOST


dnl ------------------------------------------------------------
dnl Checks for programs. 
dnl ------------------------------------------------------------
AC_PROG_AWK
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_CPP


dnl ------------------------------------------------------------
dnl Checks for libraries.
dnl ------------------------------------------------------------
dnl NOTE - Messages to the user is deffered, such that the user
dnl can have all messages at one time.

dnl Check for SDL version.
SDL_VERSION=1.2.2
AM_PATH_SDL($SDL_VERSION, have_SDL=yes, have_SDL=no)
dnl Should the -lSDL go in here? Maybe not.
XARMAN_CXXFLAGS="$XARMAN_CXXFLAGS $SDL_CXXFLAGS"
XARMAN_LIBS="$XARMAN_LIBS $SDL_LIBS"

dnl Check for SDL extension libs
saved_LIBS="$LIBS"
LIBS="$saved_LIBS $XARMAN_LIBS"

dnl SDL_mixer
AC_CHECK_LIB( SDL_mixer, Mix_OpenAudio, 
	      have_SDL_mixer=yes, have_SDL_mixer=no )

if test "x$have_SDL_mixer" = "xyes" ; then 
    XARMAN_LIBS="$XARMAN_LIBS -lSDL_mixer"
fi

dnl SDL_image
AC_CHECK_LIB( SDL_image, IMG_Load, 
	      have_SDL_image=yes, have_SDL_image=no )
if test "x$have_SDL_image" = "xyes" ; then
    XARMAN_LIBS="$XARMAN_LIBS -lSDL_image"
fi

LIBS="$saved_LIBS"


dnl ------------------------------------------------------------
dnl Checks for header files. (Unused?)
dnl ------------------------------------------------------------
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_CHECK_HEADERS(sys/time.h unistd.h)


dnl ------------------------------------------------------------
dnl Checks for typedefs, structures, and compiler characteristics.
dnl ------------------------------------------------------------
AC_C_CONST
AC_TYPE_SIZE_T
AC_HEADER_TIME


dnl ------------------------------------------------------------
dnl Check for special functions (unused)
dnl ------------------------------------------------------------
AC_CHECK_FUNCS(getcwd)


dnl ------------------------------------------------------------
dnl General options
dnl ------------------------------------------------------------

WFLAGS="-Wall -Wpointer-arith -Wconversion"
OFLAGS="-O2 -ffast-math -fexpensive-optimizations"
EONPFLAGS="-fomit-frame-pointer"

XARMAN_CXXFLAGS="$XARMAN_CXXFLAGS $WFLAGS"
XARMAN_OP_CXXFLAGS=$OFLAGS

dnl ------------------------------------------------------------
dnl Set optimization flags for platform - unused
dnl ------------------------------------------------------------
dnl case "$host" in
dnl i*86-*-*) XARMAN_OP_CXXFLAGS="$XARMAN_OP_CXXFLAGS -malign-loops=2 -malign-jumps=2 -malign-functions=2";
dnl alpha*-*-linux-*) XARMAN_CXXFLAGS="$XARMAN_CXXFLAGS -mieee";;
dnl esac


dnl ------------------------------------------------------------
dnl debug, optimize, pedantic and profile options
dnl ------------------------------------------------------------
AC_ARG_ENABLE(debug,     [  --disable-debug         Produce an executable without debugging symbols], 
			 [disable_debug=yes], [disable_debug=no])


if test "x$disable_debug" = "xno" ; then 
  AC_DEFINE(DEBUG, 1, High level debug setting)
  XARMAN_CXXFLAGS="-g $XARMAN_CXXFLAGS"
  AC_CHECK_HEADER(execinfo.h, [AC_DEFINE(HAVE_EXECINFO_H, 1, Wheter or not execinfo.h is present)
		 XARMAN_LIBS="$XARMAN_LIBS -rdynamic"])
fi

AC_ARG_ENABLE(optimize,  [  --enable-optimize       Enable various optimizations. Looooong compile time],
                         [enable_optimize=yes], [enable_optimize=no])

AC_ARG_ENABLE(optimize-size,  [  --enable-optimize-size  Enable optimization for size. Only relevante in contest.],
			 [XARMAN_CXXFLAGS="$XARMAN_CXXFLAGS -O" ])

AC_ARG_ENABLE(pedantic,  [  --enable-pedantic       Enable -pedantic (and -ansi for C) when compiling], 
                         [XARMAN_CXXFLAGS="$XARMAN_CXXFLAGS -ansi -pedantic"])

AC_ARG_ENABLE(profile,   [  --enable-profile        Produce a profiled executable],
                         [enable_profile=yes], [enable_profile=no])

dnl Set optimize flags
if test "x$enable_optimize" = "xyes" ; then
  XARMAN_CXXFLAGS="$XARMAN_CXXFLAGS $XARMAN_OP_CXXFLAGS"
  if test "x$enable_profile" = "xno" ; then
    XARMAN_CXXFLAGS="$XARMAN_CXXFLAGS $EONPFLAGS"
  fi
fi

dnl Set profile flags
if test "x$enable_profile" = "xyes" ; then
  XARMAN_CXXFLAGS="$XARMAN_CXXFLAGS -pg -O"; 
fi

dnl ------------------------------------------------------------
dnl Specify data directory - stolen from tuxkart
dnl ------------------------------------------------------------

dnl I am not exactly sure about datarootdir vs datadir, but here goes.
MY_EXPAND_DIR(xarman_datadir, "$datarootdir/games/$PACKAGE")
AC_DEFINE_UNQUOTED(XARMAN_DATADIR, "$xarman_datadir", Defines the location of the data directory)

dnl AC_ARG_WITH(data-dir, [  --with-data-dir=PATH    Default xarman data directory], 
dnl                      XARMAN_CPPFLAGS="$XARMAN_CPPFLAGS -DDATA_DIR=\\\"$withval\\\"")




dnl ------------------------------------------------------------
dnl Print messages about missing or incomplete stuff.
dnl ------------------------------------------------------------
AC_MSG_CHECKING(if there were any problems with the environment)

have_trouble=no
if test "x$have_SDL" = "xno" ; then
    have_trouble=yes
    AC_MSG_WARN([
*** PROBLEM:
*** Unable to find a version of SDL that was never than 1.2.2
*** This is required for xarman to work.
*** Most distributions include at least SDL 1.2.2 - never
*** versions may be found at http://www.libsdl.org
])
fi

if test "x$have_SDL_image" = "xno" ; then 
    have_trouble=yes
    AC_MSG_WARN([
*** PROBLEM:
*** Unable to find SDL_image library
*** This is required for xarman to work.
*** Most Linux distributions include at least SDL_image 1.1 - never
*** versions may be found at http://www.libsdl.org
])
fi

if test "x$have_SDL_mixer" = "xno" ; then 
    have_trouble=yes
    AC_MSG_WARN([
*** PROBLEM:
*** Unable to find SDL_mixer library (optional)
*** This is required for music and sound support in xarman
*** and is required for xarman to work.
*** Most Linux distributions include at least SDL_mixer 1.1 - never
*** versions may be found at http://www.libsdl.org
])
fi

dnl Final check, test for any troubles
if test "x$have_trouble" != "xno" ; then
    AC_MSG_ERROR([Unable to continue])
fi

AC_MSG_RESULT(no)

dnl ------------------------------------------------------------
dnl Set final flags, output Makefiles.
dnl ------------------------------------------------------------

dnl Set the final compiler and linker flags

CPPFLAGS="$XARMAN_CPPFLAGS"
CXXFLAGS="$XARMAN_CXXFLAGS"
LIBS="$XARMAN_LIBS"

AC_OUTPUT(data/Makefile data/graphics/Makefile data/sounds/Makefile src/Makefile Makefile xarman.spec)
