
CC=gcc
CFLAGS=-Wextra -Wall -pedantic -g # -std=c99 -Werror

BINDIR=bin
SRCDIR=src
OBJDIR=obj

ALLSRC= $(shell find $(SRCDIR) -name "*.c")
SRC = $(shell for file in $(ALLSRC); do if [ -s $$file ]; then echo $$file; fi; done)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)


.PHONY: all

all: main

main : $(OBJ) 
	@if [ ! -d "$(BINDIR)" ]; then mkdir $(BINDIR); fi
	$(CC) $^ -o $(BINDIR)/$@ $(CFLAGS) 




$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@if [ ! -f "$@" ]; then \
		mkdir -p $(shell dirname $@); \
	fi
	$(CC) -c $< -o $@ $(CFLAGS);


clean:
	@rm -rf $(BINDIR)
	@rm -rf $(OBJDIR)

