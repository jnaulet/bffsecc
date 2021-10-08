SOURCE := $(wildcard *.c)
UNIT := $(SOURCE:%.c=%.unit)

CFLAGS := -I../../include -DUNIT_TESTS

all: $(UNIT)

%.unit: %.c FORCE
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	@rm -f $(UNIT)

.PHONY: FORCE
