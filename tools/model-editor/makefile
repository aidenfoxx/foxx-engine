# Build paths
OBJ_DIR=build
LIB_DIR=../../lib
BIN_DIR=../../bin
SRC_DIR=../../src
INC_DIR=../../include

# Standard Build Flags
CC=gcc
CFLAGS=-o -std=c99 -pedantic -c -Wall -g -I $(INC_DIR) `pkg-config --cflags gtk+-3.0`

ifeq ($(OS), Windows_NT)
	LDFLAGS=-L $(LIB_DIR) -lglfw3dll -lopengl32 -glu32 `pkg-config --libs gtk+-3.0`
else
	LDFLAGS=-lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl `pkg-config --libs gtk+-3.0`
endif

# Files
SRC=$(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*/*/*.c)
SRC:=$(subst ../../src/main.c, main.c, $(SRC))
OBJ=$(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
BIN=model-editor

# Build
all: $(addprefix $(BIN_DIR)/, $(BIN))

$(addprefix $(BIN_DIR)/, $(BIN)): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(OBJ_DIR)/main.o: main.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/*/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJ)