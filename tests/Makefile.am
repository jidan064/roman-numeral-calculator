## Process file with automake to produce Makefile.in

TESTS = check_calculator
check_PROGRAMS = check_calculator
check_calculator_SOURCES = check_calculator.c $(top_builddir)/src/RomanNumeral.h
check_calculator_CFLAGS = @CHECK_CFLAGS@
check_calculator_LDADD = $(top_builddir)/src/libcalculator.la @CHECK_LIBS@
