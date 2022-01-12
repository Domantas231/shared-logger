CC:=gcc
SRC:=$(wildcard *.c)
OBJS:=$(SRC:.c=.o)
BINS:=(random print_log)

PREFIX:=/usr

.PHONY: all install uninstall clean

all: $(OBJS)

%.c: %.o
	$(CC) -c $^

install:
	install -d $(PREFIX)/bin
	install -m 644 random $(PREFIX)/bin/random
	install -m 644 print_log $(PREFIX)/bin/print_log

uninstall:
	$(RM) $(PREFIX)/bin/random
	$(RM) $(PREFIX)/bin/print_log

clean:
	$(RM) $(OBJS) $(BINS)