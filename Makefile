# директории
SRC_DIR=./src/
OBJ_DIR=./obj/
BIN_DIR=./bin/
HEADERS_DIR=./headers/

# компилятор
CC=gcc

# имя выходного файла
OUT_FILENAME=runme

# мои библиотеки
ARCHIVATOR=archivator_by_IVAN
TREE=tree_by_IVAN

all : directories main.o $(ARCHIVATOR).o $(TREE).o
	$(CC) $(OBJ_DIR)main.o $(OBJ_DIR)$(ARCHIVATOR).o $(OBJ_DIR)$(TREE).o -o $(BIN_DIR)$(OUT_FILENAME)
	$(BIN_DIR)$(OUT_FILENAME)
	
main.o : 
	$(CC) -I$(HEADERS_DIR) $(SRC_DIR)main.c -c -o $(OBJ_DIR)main.o

$(ARCHIVATOR).o : 
	$(CC) -I$(HEADERS_DIR) $(SRC_DIR)$(ARCHIVATOR).c -c -o $(OBJ_DIR)$(ARCHIVATOR).o

$(TREE).o :
	$(CC) -I$(HEADERS_DIR) $(SRC_DIR)$(TREE).c -c -o $(OBJ_DIR)$(TREE).o

directories : 
	mkdir -p obj
	mkdir -p bin

clean : 
	rm -rf $(OBJ_DIR)*
	rm -rf $(BIN_DIR)*
