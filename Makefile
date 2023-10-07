CC := gcc
CFLAGS := `sdl2-config --libs --cflags` -lSDL2
SRCS := main.c
OBJS := $(SRCS:.c=.o)
EXEC := run

$(EXEC): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)