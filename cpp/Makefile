CC := g++
BUILD_DIR := build
INCLUDE_DIR := include
SRC_DIR := src
CFLAGS := -Wall -Iinclude -I/usr/include/SDL2 `sdl2-config --libs --cflags` -lSDL2 -lSDL2_ttf
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

EXEC := run

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(EXEC) $(BUILD_DIR)/*

