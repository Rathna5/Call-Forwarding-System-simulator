CC = gcc 
CFLAGS = -Wall -c -g
LDFLAGS = -o

INC = ./inc/
SRC = ./src
OBJ = ./obj
BIN = ./bin

IFLAGS = -I $(INC)

all: CFSS

CFSS: $(OBJ)/main.o $(OBJ)/common.o $(OBJ)/user.o $(OBJ)/cfss.o 
	$(CC) $(LDFLAGS) $(BIN)/CFSS $(OBJ)/main.o $(OBJ)/common.o $(OBJ)/user.o $(OBJ)/cfss.o 

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) $(SRC)/main.c $(IFLAGS)
	mv main.o $(OBJ)/

$(OBJ)/common.o: $(SRC)/common.c
	$(CC) $(CFLAGS) $(SRC)/common.c $(IFLAGS)
	mv common.o $(OBJ)/

$(OBJ)/user.o: $(SRC)/user.c
	$(CC) $(CFLAGS) $(SRC)/user.c $(IFLAGS)
	mv user.o $(OBJ)/

$(OBJ)/cfss.o: $(SRC)/cfss.c
	$(CC) $(CFLAGS) $(SRC)/cfss.c $(IFLAGS)
	mv cfss.o $(OBJ)/

clean:
	rm -f $(OBJ)/*
	rm -f $(BIN)/*
	@echo "Cleaning Done!"
