#Misc Variables
LIBNAME = mygl

# Paths
APPS = ./apps
BIN = ./bin
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj
SRC = ./src

# Compiler flags
CC = gcc
FLAGS = -O3 -Wall
LIBS = -lGL -lGLU -lglut -lm -l$(LIBNAME) -L $(LIB)

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all: \
	build \
	app

build: $(OBJS)
		ar -rcs  $(LIB)/lib$(LIBNAME).a $(OBJS)

app: clean_apps \
	$(BIN)/app

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	$(CC) $(FLAGS) -c $< -I $(INCLUDE) -o $@

$(BIN)/%: $(APPS)/%.c
	$(CC) $(FLAGS) $< $(LIBS) $(LIB)/* -I $(INCLUDE) -o $@

run:
	$(BIN)/app

clean:
	rm -rf $(BIN)/* $(LIB)/* $(OBJ)/*

clean_apps:
	rm -rf $(BIN)/*
