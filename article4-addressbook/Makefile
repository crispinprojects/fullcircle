#--------------------------------------------------------------
# GTK4 Makefile (Ubuntu 24.04)
# Author: Alan Crispin <crispinalan@gmail.com> 
# Date: July 2025
# Changelog: 0.04
#----------------------------------------------------------------

CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk4)
# turn on all warnings (-Wall)
# use debugging information (-g) 
# maximum optimization (-O3).

CFLAGS += -Wall
#CFLAGS += -g
#CFLAGS += -O3

LIBS = $(shell $(PKGCONFIG) --libs gtk4) 

SRC = main.c person-contact.c

OBJS = $(SRC:.c=.o)

all: addressbook


%.o: %.c
	$(CC) -c -o $(@F) $(CFLAGS) $<


addressbook: $(OBJS)
	$(CC) -o $(@F) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)
	rm -f addressbook
install:
	echo "Installing is not supported"
run:
	./addressbook
