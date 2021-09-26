APP := example
PWD := $(shell pwd)

SOURCES := $(wildcard *.c)
OBJ := $(SOURCES:.c=.o)

UNIT_TESTS := $(SOURCES:.c=.test)

INCLUDE := -I../include
CFLAGS := -Wall -Wextra -D__X86_64__ -g $(INCLUDE)
SPLINTFLAGS := -badflag +posixlib

all: $(APP) $(UNIT_TESTS)
#	Run unit tests anyway
	@for test in $(UNIT_TESTS); do \
	  $(PWD)/$$test > /dev/null; true; \
	done

# App
$(APP): $(OBJ)
	$(CC) $< -o $@

# Obj
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Unit tests
%.test: %.c FORCE
	@$(CC) $(CFLAGS) -DRUN_UNIT_TESTS $< -o $@

splint:
	splint $(SPLINTFLAGS) $(CFLAGS) $(SOURCES)

clean:
	@rm -f $(APP) $(OBJ) $(UNIT_TESTS)

.PHONY: FORCE
