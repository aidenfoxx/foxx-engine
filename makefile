# Build paths
OBJ_DIR=build
LIB_DIR=lib
BIN_DIR=bin
SRC_DIR=src
INC_DIR=include

# Standard Build Flags
CC=gcc
CFLAGS=-o -std=c99 -pedantic -c -Wall -I $(INC_DIR) -g

ifeq ($(OS), Windows_NT)
    LDFLAGS=-L $(LIB_DIR) -lglfw3dll -lopengl32
else
    LDFLAGS=-lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl
endif

# Files
SRC=$(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
OBJ=$(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
BIN=foxx

# Build
all: $(SRC) $(addprefix $(BIN_DIR)/, $(BIN))

$(addprefix $(BIN_DIR)/, $(BIN)): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJ)
