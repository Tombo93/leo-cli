CC ?= gcc
CFLAGS=-g -m64 -Wall -Werror -Wunused-parameter -Wunused-variable -O3
# LDFLAGS

SRC_DIR = ./src
BUILD_DIR = ./build
TEST_DIR = ./tests

SRCS := $(shell find $(SRC_DIR)) -name *.c
OBJS := $(addsuffix .o, $(basename $(SRCS)))
MAIN_EXEC = main.out


all: $(BUILD_DIR)/$(MAIN_EXEC)

$(BUILD_DIR)/$(MAIN_EXEC): $(BUILD_DIR)/$(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/$(OBJS): $(SRC_DIR)/$(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)