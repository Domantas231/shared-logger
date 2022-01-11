CC:=gcc
SRC:=$(wildcard *.c)
OBJS:=$(SRC:.c=.o)
BIN:=random

PREFIX:=/usr

.PHONY: all install uninstall clean

all: $(OBJS)

%.c: %.o
	$(CC) -c $^

install:
	install -d $(PREFIX)/bin
	install -m 644 $(BIN) $(PREFIX)/bin/$(BIN)

uninstall:
	$(RM) $(PREFIX)/bin/$(BIN)

clean:
	$(RM) $(OBJS) $(BIN)