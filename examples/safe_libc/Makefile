TOP := ../..
LIB := safe_libc.a

SRC := $(wildcard src/*.c)
OBJ := $(SRC:%.c=%.o)

INCLUDE := -Iinclude -I$(TOP)/include
CFLAGS := -Wall -Wextra $(INCLUDE)
SPLINTFLAGS := -checks -exportlocal

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) rcs $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

splint:
	splint $(SPLINTFLAGS) $(INCLUDE) $(SRC)

clean:
	-rm -f $(OBJ) $(LIB)
