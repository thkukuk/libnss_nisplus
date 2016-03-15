#
# Copyright (c) 2015 Thorsten Kukuk, Germany
#
# Author: Thorsten Kukuk <kukuk@thkukuk.de>
#
# Process this file with automake to produce Makefile.in.
#

CLEANFILES = *~

EXTRA_DIST = libnss_nisplus.map

AM_CFLAGS = -D_REENTRANT=1 -DNIS_INTERNAL=1
AM_CPPFLAGS = -I$(srcdir) @TIRPC_CFLAGS@ @LIBNSL_CFLAGS@

lib_LTLIBRARIES = libnss_nisplus.la

noinst_HEADERS = libc-lock.h nss-nisplus.h netgroup.h nisplus-parser.h
check_PROGRAMS = nss_loader-test
nss_loader_test_LDADD = -ldl

TESTS = $(check_PROGRAMS)

libnss_nisplus_la_LDFLAGS = -version-info 2:0:0 \
	-Wl,--version-script=$(srcdir)/libnss_nisplus.map
libnss_nisplus_la_LIBADD = @LIBNSL_LIBS@ @TIRPC_LIBS@
libnss_nisplus_la_SOURCES = nisplus-alias.c nisplus-ethers.c nisplus-grp.c \
	nisplus-hosts.c nisplus-initgroups.c nisplus-netgrp.c \
	nisplus-network.c nisplus-parser.c nisplus-proto.c \
	nisplus-publickey.c nisplus-pwd.c nisplus-rpc.c nisplus-service.c \
	nisplus-spwd.c nss-nisplus.c
