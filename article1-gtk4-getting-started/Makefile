#--------------------------------------------------------------
# GTK4 Makefile (Ubuntu 24.04)
# Author: Alan Crispin <crispinalan@gmail.com> 
# Date: July 2025
# Changelog: 0.04
#----------------------------------------------------------------
CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk4)
LIBS = $(shell $(PKGCONFIG) --libs gtk4) 
SRC = main.c
OBJS = $(SRC:.c=.o)
all: demo
%.o: %.c
	$(CC) -c -o $(@F) $(CFLAGS) $<
demo: $(OBJS)
	$(CC) -o $(@F) $(OBJS) $(LIBS)
clean:
	rm -f $(OBJS)
	rm -f demo
install:
	echo "Installing is not supported"
run:
	./demo

