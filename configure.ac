AC_PREREQ(2.69)

AC_INIT([quemath], [0.1.0], [jay@jaydolan.com])

#AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([quemath/quemath.h])

AC_CANONICAL_HOST

AC_GNU_SOURCE

AC_PROG_CC
AC_PROG_CC_STDC
AC_PROG_LIBTOOL

AM_INIT_AUTOMAKE([foreign])
AM_SILENT_RULES([yes])

AH_TOP([#pragma once])

HOST_NAME=""
HOST_CFLAGS=""

AC_MSG_CHECKING([host type])
case "$host" in
	*-apple-*)
		HOST_NAME="APPLE"
		AC_MSG_RESULT(apple)
		;;
	*-mingw*)
		HOST_NAME="MINGW"
		AC_MSG_RESULT(mingw)
		;;
	*)
		HOST_NAME="LINUX"
		AC_MSG_RESULT(linux)
		;;
esac

AC_SUBST(HOST_NAME)
AC_SUBST(HOST_CFLAGS)

AM_CONDITIONAL([APPLE], [test "x$HOST_NAME" = "xAPPLE"])
AM_CONDITIONAL([MINGW], [test "x$HOST_NAME" = "xMINGW"])
AM_CONDITIONAL([LINUX], [test "x$HOST_NAME" = "xLINUX"])

AC_CHECK_HEADERS([x86intrin.h])

PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])

AC_CONFIG_FILES([
	Makefile
	quemath/Makefile
	test/Makefile
])

AC_OUTPUT
