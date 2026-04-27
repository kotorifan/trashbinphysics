CC := cc
CCFLAGS := -O3 -std=c99 -pedantic -Wall -Wextra  -Wno-missing-braces
LDFLAGS := -lraylib -lm
SRC_DIR := src
DST_DIR := dst

SRCS := $(shell find $(SRC_DIR) -name "*.c" -type f)
OBJS := $(SRCS:%=$(DST_DIR)/%.o)

physics: $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(DST_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c $< -o $@

.PHONY: clean gendocs

clean:
	rm -r $(DST_DIR)
	rm physics
run:
	./physics

gendocs:
	doxygen Doxyfile
