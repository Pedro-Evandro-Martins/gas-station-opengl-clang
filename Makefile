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

SRCS = $(shell find $(SRC) -name '*.c')
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all: \
	build \
	app

build: $(OBJS)
		ar -rcs  $(LIB)/lib$(LIBNAME).a $(OBJS)

app: clean_apps \
	$(BIN)/app

# $(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
# 	$(CC) $(FLAGS) -c $< -I $(INCLUDE) -o $@
$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	# $(CC) $(FLAGS) -c $< -I $(INCLUDE) -o $@
	$(CC) $(FLAGS) -I $(INCLUDE) -c $< -o $@


$(BIN)/%: $(APPS)/%.c
	# $(CC) $(FLAGS) $< $(LIBS) $(LIB)/* -I $(INCLUDE) -o $@
	$(CC) $(FLAGS) -I $(INCLUDE) $< -L$(LIB) $(LIBS) -o $@

run:
	$(BIN)/app

clean:
	rm -rf $(BIN)/* $(LIB)/* $(OBJ)/*

clean_apps:
	rm -rf $(BIN)/*
