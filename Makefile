# GCC with OpenMP enabled
CP = gcc -fopenmp
override CFLAGS += -Wall -c

# Directories
BIN = ./bin
OBJ = ./build
INC = ./include
SRC = ./src

.PHONY: all dirs
.PRECIOUS: $(OBJ)/%.o

all: dirs $(BIN)/serial $(BIN)/parallel

$(BIN)/%: $(OBJ)/main.o $(OBJ)/%.o
	$(CP) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.c $(INC)/cet107.h
	$(CP) $(CFLAGS) -o $@ $< -I $(INC)

dirs: $(BIN) $(OBJ)

$(BIN): 
	@mkdir $(BIN)

$(OBJ): 
	@mkdir $(OBJ)

clean:
	@rm -f $(BIN)/* $(OBJ)/*