CC ?= gcc
CFLAGS = -g -m64 -Wall -Werror -Wunused-parameter -Wunused-variable -O3
LDFLAGS = -lcurl -lncurses -ltidy

SRC_DIR = ./src
INCLUDE_DIR = ./include
BUILD_DIR = ./build
BIN_DIR = $(BUILD_DIR)/bin
TEST_DIR = ./tests

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
BIN := $(BIN_DIR)/leocli


all: $(BIN)

$(BIN): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -I$(INCLUDE_DIR) -o $@

$(BIN_DIR):
	mkdir $@


.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)/*
	$(RM) $(TEST_DIR)/*.out

.PHONY: run
run:
	$(BIN) "testa"

.PHONY: test
test:
	@echo "\nCompiling tests\n"
	$(CC) $(TEST_DIR)/tests.c -o $(TEST_DIR)/test.out
	@echo "\nTesting... \n"
	$(TEST_DIR)/test.out