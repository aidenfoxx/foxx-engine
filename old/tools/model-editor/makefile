# Build paths
OBJ_DIR=build
SRC_DIR=src
INC_DIR=include

MAIN_LIB_DIR=../../lib
MAIN_BIN_DIR=../../bin
MAIN_SRC_DIR=../../src
MAIN_INC_DIR=../../include

# Standard Build Flags
CC=gcc
CFLAGS=-o -std=c99 -pedantic -c -Wall -g -I $(INC_DIR) -I $(MAIN_INC_DIR) `pkg-config --cflags gtk+-3.0`

ifeq ($(OS), Windows_NT)
	LDFLAGS=-L $(MAIN_LIB_DIR) -lfreeglut.dll -larchive.dll -lopengl32 -glu32 `pkg-config --libs gtk+-3.0`
else
	LDFLAGS=-lfreeglut -larchive -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl `pkg-config --libs gtk+-3.0`
endif

# Files
SRC_ALL=$(wildcard $(SRC_DIR)/*.c) $(wildcard $(MAIN_SRC_DIR)/*.c) $(wildcard $(MAIN_SRC_DIR)/*/*.c) $(wildcard $(MAIN_SRC_DIR)/*/*/*.c)
# Remove the main.c from the main project
SRC=$(subst $(MAIN_SRC_DIR)/main.c, , $(SRC_ALL))
OBJ=$(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
BIN=model-editor

# Build
all: $(addprefix $(MAIN_BIN_DIR)/, $(BIN))

$(addprefix $(MAIN_BIN_DIR)/, $(BIN)): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(MAIN_SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(MAIN_SRC_DIR)/*/%.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(MAIN_SRC_DIR)/*/*/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJ)