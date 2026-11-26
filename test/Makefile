
CC      ?= gcc
AR      ?= ar
CFLAGS  ?= -Wall -Wextra -O2 -std=c11

PREFIX    ?= /usr/local
LIBDIR    ?= $(PREFIX)/lib
INCLUDEDIR ?= $(PREFIX)/include

NAME    := ubox
LIB     := lib$(NAME).a

SRC     := ../src/memory.c ../src/string.c
OBJ     := $(SRC:../src/%.c=build/%.o)
HEADER  := ../src/ubox.h

TEST    := test.c
TESTBIN := build/test

.PHONY: all clean install uninstall test

all: $(LIB)

build:
	mkdir -p build

build/%.o: ../src/%.c $(HEADER) | build
	$(CC) $(CFLAGS) -I../src -c $< -o $@

$(LIB): $(OBJ)
	$(AR) rcs $@ $^

$(TESTBIN): $(TEST) $(LIB) $(HEADER) | build
	$(CC) $(CFLAGS) -I../src $(TEST) $(LIB) -o $@

test: $(TESTBIN)
	./$(TESTBIN)

install: $(LIB)
	install -d $(DESTDIR)$(LIBDIR)
	install -d $(DESTDIR)$(INCLUDEDIR)
	install -m 644 $(LIB) $(DESTDIR)$(LIBDIR)/$(LIB)
	install -m 644 $(HEADER) $(DESTDIR)$(INCLUDEDIR)/$(NAME).h

uninstall:
	rm -f $(DESTDIR)$(LIBDIR)/$(LIB)
	rm -f $(DESTDIR)$(INCLUDEDIR)/$(NAME).h

clean:
	rm -rf build $(LIB)

