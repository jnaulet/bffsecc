TOP := ../../../..
SRC := $(wildcard *.c)
UNIT_TEST := $(SRC:%.c=%.unit)

CFLAGS := -DNDEBUG
CFLAGS += -I../../include
CFLAGS += -I$(TOP)/include

all: $(UNIT_TEST)

%.unit: %.c FORCE
	$(CC) $(CFLAGS) $< -o $@

.PHONY: FORCE
