# Makefile for Deep, Copyright (C) 2002 Jacob Kroon
NAME		= deep
VERSION		= 0.1.16
CC		= gcc
CFLAGS		+= -D_VERSION=\"$(VERSION)\" -Wall -g \
		   $(shell sdl-config --cflags)
LDFLAGS		= $(shell sdl-config --libs) -lGL
CSOURCES	= video.c camera.c vector.c mesh.c level.c being.c perlin.c \
		  list.c entity.c square.c gui.c timer.c
INCLUDES	= video.h camera.h vector.h mesh.h level.h being.h perlin.h \
		  list.h entity.h square.h gui.h timer.h

#############################

OBJS=$(CSOURCES:.c=.o)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME):$(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	$(MAKE) -C tests clean
	rm -rf *~ $(OBJS) $(NAME)

indent:
	$(MAKE) -C tests indent
	indent -br -brs -sob -ce -c50 -npsl -npcs $(CSOURCES) $(INCLUDES)
	rm -rf *~

dist:
	$(MAKE) indent
	$(MAKE) clean
	mkdir $(NAME)-$(VERSION)
	cp -r $(CSOURCES) $(INCLUDES) COPYING Makefile tests \
	   $(NAME)-$(VERSION)
	tar -cf $(NAME)-$(VERSION).tar $(NAME)-$(VERSION)
	gzip -9 $(NAME)-$(VERSION).tar
	rm -rf $(NAME)-$(VERSION)
