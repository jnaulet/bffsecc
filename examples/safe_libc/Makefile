TOP := ../..
LIB := safe_libc.a

SRC := $(wildcard src/*.c)
OBJ := $(SRC:%.c=%.o)

INCLUDE := -Iinclude -I$(TOP)/include
CFLAGS := -Wall -Wextra $(INCLUDE)

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) rcs $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

splint:
	splint $(INCLUDE) $(SRC)

clean:
	-rm -f $(OBJ) $(LIB)
