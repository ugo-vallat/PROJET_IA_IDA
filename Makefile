
CC=gcc
CFLAGS=-Wextra -Wall -pedantic -g -rdynamic

BINDIR=bin
SRCDIR=src
OBJDIR=obj
MODDIR=modules
DATADIR=data-structure
TESTDIR=test

ALLSRC= $(shell find $(SRCDIR)/$(MODDIR) $(SRCDIR)/$(DATADIR)  -name "*.c")
SRC = $(shell for file in $(ALLSRC); do if [ -s $$file ]; then echo $$file; fi; done)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# prise en charge du mode DEBUG
ifeq ($(DEBUG),yes)
	CFLAGS+=-DDEBUG 
else
	CFLAGS+=-DNDEBUG
endif


.PHONY: all

all: main

# compilation du main 
main : $(OBJ) $(OBJDIR)/main.o $(OBJDIR)/dataTest.o | create_bin_dir
	$(CC) $^ -o $(BINDIR)/$@ $(CFLAGS) 



# compilation des test
test_depth : tdepth

test_ida : tida

t% : $(OBJDIR)/test_%.o $(OBJDIR)/dataTest.o $(OBJ) | create_bin_dir
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS) -DDEBUG


# compilation des .o de src
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@if [ ! -f "$@" ]; then \
		mkdir -p $(shell dirname $@); \
	fi
	$(CC) -c $< -o $@ $(CFLAGS);


# compilation des .o de test
$(OBJDIR)/%.o: $(TESTDIR)/%.c
	@if [ ! -f "$@" ]; then \
		mkdir -p $(shell dirname $@); \
	fi
	$(CC) -c $< -o $@ $(CFLAGS);


# création des répertoires 
create_bin_dir : 
	@if [ ! -d "$(BINDIR)" ]; then mkdir $(BINDIR); fi




clean:
	@rm -rf $(BINDIR)
	@rm -rf $(OBJDIR)

