
CC=gcc
CFLAGS=-Wextra -Wall -pedantic -g 

BINDIR=bin
SRCDIR=src
OBJDIR=obj
MODDIR=modules
DATADIR=data-structure

ALLSRC= $(shell find $(SRCDIR)/$(MODDIR) $(SRCDIR)/$(DATADIR)  -name "*.c")
SRC = $(shell for file in $(ALLSRC); do if [ -s $$file ]; then echo $$file; fi; done)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# prise en charge du mode DEBUG
ifeq ($(DEBUG),yes)
	CFLAGS+=-DDEBUG 
else
	CFLAGS=-DNDEBUG
endif


.PHONY: all

all: main


main : $(OBJ) $(OBJDIR)/main.o
	echo $(SRC)
	@if [ ! -d "$(BINDIR)" ]; then mkdir $(BINDIR); fi
	$(CC) $^ -o $(BINDIR)/$@ $(CFLAGS) 

main2 : $(OBJ) $(OBJDIR)/main2.o
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

