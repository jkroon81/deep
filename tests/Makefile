# Makefile for Higher Tests, Copyright (C) 2002 Jacob Kroon
NAMES		= test_shapes test_level test_perlin
CC		= gcc
CFLAGS		+= -I.. $(shell sdl-config --cflags) -Wall -g
LDFLAGS		= $(shell sdl-config --libs) -lGL
CSOURCES	= test_shapes.c test_level.c test_perlin.c
COMMON_O	= ../video.o ../camera.o ../vector.o ../mesh.o
SHAPES_O	= $(COMMON_O) test_shapes.o
LEVEL_O		= $(COMMON_O) test_level.o ../level.o ../being.o ../perlin.o \
		  ../list.o ../entity.o ../square.o ../gui.o ../timer.o
PERLIN_O	= $(COMMON_O) test_perlin.o ../perlin.o

#############################

OBJS=$(CSOURCES:.c=.o)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

all : $(NAMES)

test_shapes : $(SHAPES_O)
	$(CC) $(SHAPES_O) $(LDFLAGS) -o test_shapes

test_level : $(LEVEL_O)
	$(CC) $(LEVEL_O) $(LDFLAGS) -o test_level

test_perlin : $(PERLIN_O)
	$(CC) $(PERLIN_O) $(LDFLAGS) -o test_perlin

clean:
	rm -rf *~ $(OBJS) $(NAMES)

indent:
	indent -br -brs -sob -ce -c50 -npsl -npcs $(CSOURCES)
	rm -rf *~
