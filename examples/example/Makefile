APP := example
PWD := $(shell pwd)
TOP := ../..

SOURCES := $(wildcard *.c)
OBJ := $(SOURCES:.c=.o)

INCLUDE := -I$(TOP)/include
CFLAGS := -Wall -Wextra -D__X86_64__ -g $(INCLUDE)
SPLINTFLAGS := -badflag +posixlib

all: $(APP)

# App
$(APP): $(OBJ)
	$(CC) $< -o $@

# Obj
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

splint:
	splint $(SPLINTFLAGS) $(CFLAGS) $(SOURCES)

clean:
	@rm -f $(APP) $(OBJ)

.PHONY: FORCE
