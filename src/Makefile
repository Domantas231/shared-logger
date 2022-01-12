CC:=gcc
LDFLAGS:=-llogger -lsqlite3 
SRC:=$(wildcard *.c)
OBJS:=$(SRC:.c=.o)
BINS:=random_log print_log

PREFIX:=/usr

.PHONY: all install uninstall clean

all: $(BINS)

random_log: random_log.o
	$(CC) -o $@ $^ $(LDFLAGS)

print_log: print_log.o
	$(CC) -g -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $^

install:
	install -d $(PREFIX)/bin
	install -m 644 random_log $(PREFIX)/bin/random_log
	install -m 644 print_log $(PREFIX)/bin/print_log

uninstall:
	$(RM) $(PREFIX)/bin/random_log
	$(RM) $(PREFIX)/bin/print_log

clean:
	$(RM) $(OBJS) $(BINS)