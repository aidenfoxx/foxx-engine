# Build paths
OBJ_DIR=build
LIB_DIR=lib
BIN_DIR=bin
SRC_DIR=src
INC_DIR=include

# Standard Build Flags
CC=gcc
CFLAGS=-o -std=c99 -pedantic -c -Wall -g -I $(INC_DIR) `pkg-config --cflags libarchive`

ifeq ($(OS), Windows_NT)
	LDFLAGS=-L $(LIB_DIR) -lfreeglut.dll -larchive.dll -lz.dll -lopengl32 -glu32 `pkg-config --libs libarchive`
else
	LDFLAGS=-L $(LIB_DIR) -lfreeglut_static -larchive_static -lz -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl `pkg-config --libs libarchive`
endif

# Files
SRC=$(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
OBJ=$(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
BIN=foxx

# Build
all: $(addprefix $(BIN_DIR)/, $(BIN))

$(addprefix $(BIN_DIR)/, $(BIN)): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJ)