dnl Process this file with autoconf to produce a configure script.
AC_INIT
AC_CONFIG_SRCDIR([sted2/sted.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE(sted2,`sed -n -e 's/^.*VERSION.*"\(.*\)"$/\1/p' ${srcdir}/sted2/version.h`)
PACKAGE="sted2"
VERSION=`sed -n -e 's/^.*VERSION.*"\(.*\)"$/\1/p' ${srcdir}/sted2/version.h`
AC_SUBST(PACKAGE)
AC_SUBST(VERSION)

dnl Checks for programs.
dnl if test -z "${CFLAGS}"; then
dnl   if test -z "${CCOPTS}"; then
dnl     CCOPTS="-O2 -fomit-frame-pointer"
dnl   fi
dnl   CFLAGS="$CCOPTS"
dnl fi

AC_PROG_CC

dnl Set of available languages.
ALL_LINGUAS="ja"
AM_GNU_GETTEXT(external)
AC_CHECK_FUNC(gettext,,AC_CHECK_LIB(intl,gettext))

dnl Misc definition
AC_PROG_INSTALL
AC_PROG_RANLIB
AC_PATH_X
AC_PATH_XTRA

dnl Checks for header files.
AC_HEADER_DIRENT
m4_warn([obsolete],
[The preprocessor macro `STDC_HEADERS' is obsolete.
  Except in unusual embedded environments, you can safely include all
  ISO C90 headers unconditionally.])dnl
# Autoupdate added the next two lines to ensure that your configure
# script's behavior did not change.  They are probably safe to remove.
AC_CHECK_INCLUDES_DEFAULT
AC_PROG_EGREP

AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS(fcntl.h sys/time.h unistd.h strings.h)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_STRUCT_TM
AC_C_CONST
AC_TYPE_PID_T
AC_TYPE_SIZE_T
m4_warn([obsolete],
[Update your code to rely only on HAVE_SYS_TIME_H,
then remove this warning and the obsolete code below it.
All current systems provide time.h; it need not be checked for.
Not all systems provide sys/time.h, but those that do, all allow
you to include it and time.h simultaneously.])dnl
AC_CHECK_HEADERS_ONCE([sys/time.h])
# Obsolete code to be removed.
if test $ac_cv_header_sys_time_h = yes; then
  AC_DEFINE([TIME_WITH_SYS_TIME],[1],[Define to 1 if you can safely include both <sys/time.h>
	     and <time.h>.  This macro is obsolete.])
fi
# End of obsolete code.


dnl Header templates
AH_TEMPLATE(PACKAGE)
AH_TEMPLATE(VERSION)
AH_TEMPLATE(HAVE_CATGETS)
AH_TEMPLATE(HAVE_GETTEXT)
AH_TEMPLATE(HAVE_LC_MESSAGES)
AH_TEMPLATE(HAVE_STPCPY)
AH_TEMPLATE(ENABLE_NLS)
AH_TEMPLATE(NO_SHM)
AH_TEMPLATE(USE_CURSES)
AH_TEMPLATE(STED_DEFAULT_PATH)
AH_TEMPLATE(STED)
AH_TEMPLATE(HAS_CURSES)
AH_TEMPLATE(USE_SUNOS_CURSES)
AH_TEMPLATE(USE_BSD_CURSES)
AH_TEMPLATE(USE_SYSV_CURSES)
AH_TEMPLATE(USE_NCURSES)
AH_TEMPLATE(NO_COLOR_CURSES)
AH_TEMPLATE(SCO_FLAVOR)
AH_TEMPLATE(NCURSES_970530)
AH_TEMPLATE(NO_SETLOCALE)
AH_TEMPLATE(NO_XSETLOCALE)
AH_TEMPLATE(NO_XLOCALE)
AH_TEMPLATE(SJIS_CODES)
AH_TEMPLATE(HAVE_MVWCHGAT)
AH_TEMPLATE(HAVE_SUPPORT_STED3)

dnl Checks for library functions.
m4_warn([obsolete],
[your code may safely assume C89 semantics that RETSIGTYPE is void.
Remove this warning and the `AC_CACHE_CHECK' when you adjust the code.])dnl
AC_CACHE_CHECK([return type of signal handlers],[ac_cv_type_signal],[AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([#include <sys/types.h>
#include <signal.h>
],
		 [return *(signal (0, 0)) (0) == 1;])],
		   [ac_cv_type_signal=int],
		   [ac_cv_type_signal=void])])
AC_DEFINE_UNQUOTED([RETSIGTYPE],[$ac_cv_type_signal],[Define as the return type of signal handlers
		    (`int' or `void').])

AC_CHECK_FUNCS(getcwd gettimeofday putenv select strstr memcpy)

dnl for defload.c
AC_DEFINE(STED)

dnl Locale definition

dnl Check for curses
AM_CONDITIONAL(HAS_CURSES, test "$has_curses" = true)
AC_CHECK_CURSES

AC_ARG_ENABLE(curses, [  --disable-curses        trun off using curses [default no]],curses_given=yes,curses_given=no)
AC_MSG_CHECKING(whether to enable curses)
if "$has_curses" = "true"; then
  if test x$enableval = xyes -o x$curses_given = xno; then
    AC_MSG_RESULT(yes)
    AC_DEFINE(USE_CURSES)
  else
    AC_MSG_RESULT(no)
  fi
else
  AC_MSG_RESULT(no)
fi

dnl Check for function 'mvwchgat' in any curses libraries

oldlibs=$LIBS
LIBS="$LIBS $CURSES_LIBS"
AC_CHECK_DECL( [mvwchgat], [AC_DEFINE(HAVE_MVWCHGAT)], [], [#include <curses.h>] )
LIBS="$oldlibs"

dnl local definitions
dnl Shared memory
AC_ARG_ENABLE(shm, [  --enable-shm            trun on using shared memory [default yes]],shm_given=yes,shm_given=no)
AC_MSG_CHECKING(whether to enable shared memory)
if test x$shm_given = xyes -o x$enableval = xno; then
  AC_MSG_RESULT(no)
  AC_DEFINE(NO_SHM)
else
  AC_MSG_RESULT(yes)
fi

dnl STED_DEFAULT_PATH
AC_ARG_WITH(default_path,
[  --with-default-path=DIR uses DIR as sted2.[cnf,fon] path],
	if test "$withval" != "NONE"; then
	sted_default_path="${withval}"
	else
	sted_default_path="/usr/local/lib/sted"
	fi,
	sted_default_path="/usr/local/lib/sted" )

AC_DEFINE_UNQUOTED(STED_DEFAULT_PATH, "${sted_default_path}")
AC_SUBST(sted_default_path)

dnl Check for SJIS environment
AC_ARG_ENABLE(sjis,
[  --enable-sjis           enable Japanese code as SJIS [default no]],
sjis_given=yes, sjis_given=no)
AC_MSG_CHECKING(wether to enable sjis conversion)
if test x$sjis_given = xyes -o x$enableval = xyes; then
  AC_MSG_RESULT(yes)
  AC_DEFINE(SJIS_CODES)
else
  AC_MSG_RESULT(no)
fi


dnl Check for X

if test "x$x_includes" = "x"; then
  x_includes="/usr/include"
fi

saved_cflags="$CFLAGS"
saved_ldflags="$LDFLAGS"

CFLAGS="$CFLAGS $X_CFLAGS"
LDFLAGS="$LDFLAGS $X_LDFLAGS $X_LIBS"

if test "x$no_x" = "xyes"; then 
  AC_MSG_ERROR([
*** X libraries or include files not found. Check 'config.log' for 
*** more details.])
fi

# Check for the X11 library
AC_CHECK_LIB(X11, XOpenDisplay, x_libs="-lX11 $X_EXTRA_LIBS", 
  AC_MSG_ERROR([*** libX11 not found. Check 'config.log' for more details.]),
  $X_EXTRA_LIBS)

if test "x$enable_shm" = "xyes"; then
  # Check for the Xext library (needed for XShm extention)
  AC_CHECK_LIB(Xext, XShmAttach, 
      x_libs="-lXext $x_libs", 
      # On AIX, it is in XextSam instead, but we still need -lXext
      AC_CHECK_LIB(XextSam, XShmAttach, 
          x_libs="-lXextSam -lXext $x_libs", 
          no_xext_lib=yes, $x_libs),
      $x_libs)
fi

x_cflags="$X_CFLAGS"
x_ldflags="$X_LDFLAGS $X_LIBS"

CFLAGS="$saved_cflags"
LDFLAGS="$saved_ldflags"

AC_SUBST(x_cflags)
AC_SUBST(x_includes)
AC_SUBST(x_ldflags)
AC_SUBST(x_libs)

dnl# this is a really hack test for some basic Xlocale stuff
SAVETHELIBS=$LIBS
LIBS="$LIBS $X_LIBS $X_PRE_LIBS $X_EXTRA_LIBS -lX11"
AC_CACHE_CHECK(for working Xlocale, sted2_cv_func_xlocale,
[AC_RUN_IFELSE([AC_LANG_SOURCE([[#define X_LOCALE 1
#include <X11/Xlocale.h>
#include <X11/Xlib.h>
main() {
char *p;
if ((p = XSetLocaleModifiers("@im=none")) != NULL && *p)
exit (XSupportsLocale() ? 0 : 1);
else
exit (1);}
]])],[rxvt_cv_func_xlocale=yes],[rxvt_cv_func_xlocale=no],[AC_MSG_WARN(Define NO_XLOCALE in config.h manually)])])

if test "${sted2_cv_func_xlocale}" = no; then
  AC_DEFINE(NO_XLOCALE)
fi
LIBS=$SAVETHELIBS

AC_CACHE_CHECK(for working X setlocale, sted2_cv_func_xsetlocale,
[AC_LINK_IFELSE([AC_LANG_PROGRAM([[#define X_LOCALE 1
#include <X11/Xlocale.h>]], [[setlocale(LC_CTYPE, "");]])],[sted2_cv_func_xsetlocale=yes],[sted2_cv_func_xsetlocale=no])])
if test "${sted2_cv_func_xsetlocale}" = no; then
  AC_DEFINE(NO_XSETLOCALE)
fi

AC_CACHE_CHECK(for working plain setlocale, sted2_cv_func_setlocale,
[AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <locale.h>]], [[setlocale(LC_CTYPE, "");]])],[sted2_cv_func_setlocale=yes],[sted2_cv_func_setlocale=no])])
if test "${sted2_cv_func_setlocale}" = no; then
  AC_DEFINE(NO_SETLOCALE)
fi

AC_DEFINE_UNQUOTED(PACKAGE, "$PACKAGE")
AC_DEFINE_UNQUOTED(VERSION, "$VERSION")

AC_CONFIG_FILES([Makefile
sted2/Makefile
sted2/sub/Makefile
sted2/sayleen/Makefile
sted2/itor/Makefile
intl/Makefile
po/Makefile.in
etc/Makefile
doc/Makefile
doc/original_docs/Makefile
contrib/Makefile
])
AC_OUTPUT
