#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(digdic, VERSION, BUG-REPORT-ADDRESS)
AC_CONFIG_SRCDIR([digdic.ico])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE(foreign)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
LT_INIT
AM_OPTIONS_WXCONFIG

# Checks for libraries.
eb_LIB_EB4
AM_PATH_WXCONFIG([2.6.0])
AM_PATH_WXRC

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
