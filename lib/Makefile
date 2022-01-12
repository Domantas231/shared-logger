CC:=gcc
LIB:=liblogger.so
LDFLAGS:=-llogger -lsqlite3
SRC:=$(wildcard *.c)
OBJS:=$(SRC:.c=.o)
BIN:=print_log

PREFIX:=/usr

all: $(LIB) print_log

$(LIB): logger.o
	$(CC) -shared -o $(LIB) $^

logger.o: logger.c
	$(CC) -c -Wall -fpic $^

install:
	install -d $(PREFIX)/lib
	install -d $(PREFIX)/include
	install -m 644 $(LIB) $(PREFIX)/lib/$(LIB)
	install -m 644 logger.h $(PREFIX)/include/logger.h

uninstall:
	$(RM) $(PREFIX)/lib/$(LIB)
	$(RM) $(PREFIX)/include/logger.h

clean:
	$(RM) $(OBJS) $(LIB) $(BIN)
