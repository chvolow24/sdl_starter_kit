CC := gcc
BUILD_DIR := build
INCLUDE_DIR := include
SRC_DIR := src
CFLAGS := -Wall -Iinclude `sdl2-config --libs --cflags` -lSDL2
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

EXEC := run

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(EXEC) $(BUILD_DIR)/*

