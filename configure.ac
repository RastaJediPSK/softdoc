#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
#AC_INIT(FULL-PACKAGE-NAME, VERSION, BUG-REPORT-ADDRESS)
#AC_INIT(main, 0.0.1, erikss@rpi.edu)
AC_INIT(main, 0.0.1)
#AM_INIT_AUTOMAKE(main, 0.0.1)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADER([include/config.h])

AC_PREFIX_DEFAULT(..)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.

#AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES(Makefile src/Makefile)
AC_OUTPUT
