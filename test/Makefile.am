check_LTLIBRARIES = libgtest.la
libgtest_la_SOURCES = (top_srcdir)/googletest/googletest/src/gtest-all.cc
libgtest_la_CPPFLAGS = -I$(top_srcdir)/googletest/googletest/include -I$(top_srcdir)/googletest/googletest
libgtest_la_LDFLAGS = -pthread

check_PROGRAMS = gtest
gtest_LDADD = libgtest.la
gtest_LDFLAGS = -pthread
gtest_CPPFLAGS = -I$(top_srcdir)/googletest/googletest/include -I$(top_srcdir)/googletest/googletest -pthread -I$(top_srcdir)/src

test_sources = \
  TestMain.cpp \
  LedDriverTest.cpp
target_sources = \
  $(top_srcdir)/src/LedDriver.c
gtest_SOURCES = $(test_sources) $(target_sources)