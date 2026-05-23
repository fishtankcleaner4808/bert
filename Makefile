CC = gcc
TARGET = bert
CFLAGS = -Wall -Wextra -std=c99 `sdl2-config --cflags`
LDFLAGS = -lSDL2 -lSDL2_ttf -lm
SRC = \
	main.c \
	player/player.c \
	enemy/enemy.c \
	tilemap/tilemap.c \
	camera/camera.c \
	render/render.c \
	game/game.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)
