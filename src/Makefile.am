# BlueALSA - Makefile.am
# Copyright (c) 2016-2020 Arkadiusz Bokowy

bin_PROGRAMS = bluealsa
SUBDIRS = asound

dbusconfdir = @DBUS_CONF_DIR@
dist_dbusconf_DATA = bluealsa.conf

bluealsa_SOURCES = \
	shared/ffb.c \
	shared/log.c \
	shared/rt.c \
	a2dp.c \
	a2dp-audio.c \
	at.c \
	audio.c \
	ba-adapter.c \
	ba-device.c \
	ba-rfcomm.c \
	ba-transport.c \
	bluealsa.c \
	bluealsa-dbus.c \
	bluealsa-iface.c \
	bluez.c \
	bluez-iface.c \
	dbus.c \
	hci.c \
	sbc.c \
	sco.c \
	utils.c \
	main.c

if ENABLE_MSBC
bluealsa_SOURCES += \
	msbc.c
endif

if ENABLE_OFONO
bluealsa_SOURCES += \
	ofono.c \
	ofono-iface.c
endif

if ENABLE_UPOWER
bluealsa_SOURCES += \
	upower.c
endif

AM_CFLAGS = \
	@AAC_CFLAGS@ \
	@OPENAPTX_CFLAGS@ \
	@FFAPTX_CFLAGS@ \
	@BLUEZ_CFLAGS@ \
	@GIO2_CFLAGS@ \
	@GLIB2_CFLAGS@ \
	@LDAC_ABR_CFLAGS@ \
	@LDAC_CFLAGS@ \
	@LIBUNWIND_CFLAGS@ \
	@MPG123_CFLAGS@ \
	@SBC_CFLAGS@

LDADD = \
	@AAC_LIBS@ \
	@FFAPTX_LIBS@ \
	@OPENAPTX_LIBS@ \
	@BLUEZ_LIBS@ \
	@GIO2_LIBS@ \
	@GLIB2_LIBS@ \
	@LDAC_ABR_LIBS@ \
	@LDAC_LIBS@ \
	@LIBUNWIND_LIBS@ \
	@MP3LAME_LIBS@ \
	@MPG123_LIBS@ \
	@SBC_LIBS@
