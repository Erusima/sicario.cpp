CFLAGS := -Wall 
INCLUDE :=
LIBS :=
CC := g++

SRC_DIR := src
OBJ_DIR := obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
PROG_NAME := sicario_cpp

all: $(PROG_NAME)

$(PROG_NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(PROG_NAME)
	rm $(OBJ_DIR)/*

.PHONY: all clean
