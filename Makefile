.PHONY: lib src install uninstall clean

all: lib src

lib:
	$(MAKE) -C ./lib

src:
	$(MAKE) -C ./src

install:
	$(MAKE) -C ./lib install
	$(MAKE) -C ./src install

uninstall:
	$(MAKE) -C ./lib uninstall
	$(MAKE) -C ./src uninstall

clean:
	$(MAKE) -C ./lib clean
	$(MAKE) -C ./src clean