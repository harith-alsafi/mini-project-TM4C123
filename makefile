# Makefile for building the executable

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Isrc

# Directories
SRC_DIR = src
TEST_DIR = test
OUT_DIR = out

# Source files (excluding src/main.c)
SRC_FILES := $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))

# Object files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(SRC_FILES))

# Executable
TARGET = $(OUT_DIR)/test_executable

# Default target
all: $(TARGET)

# Rule to build object files
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the executable
$(TARGET): $(OBJ_FILES) $(TEST_DIR)/test.c
	$(CC) $(CFLAGS) $^ -o $@

# Clean rule
clean:
	rm -f $(OUT_DIR)/*.o $(TARGET)
