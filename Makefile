#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa tp0
# Autor		: Henrique Lucas Gomes Rezende
# Histórico	: 23-09-22 - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#		    : make execut - gera os arquivos .o e .bin 
#		    : make quick1 - executa os testes com o QuickSort Versão 1
#		    : make quick2 - executa os testes com o QuickSort Versão 2
#		    : make quick3 - executa os testes com o QuickSort Versão 3
#		    : make quick4 - executa os testes com o QuickSort Versão 4
#		    : make quick5 - executa os testes com o QuickSort Versão 5
#		    : make todos - executa os testes com o QuickSort capeão, MergeSort e HeapSort
#		    : make execut - gera os arquivos .o e .bin 
#		    : make clean - remove objetos e executável
#---------------------------------------------------------------------
#

# cc and flags
CC = g++
CXXFLAGS = -std=c++11 -g -Wall
#CXXFLAGS = -std=c++11 -O3 -Wall

# folders
INCLUDE_FOLDER = ./include/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/

# all sources, objs, and header files
MAIN = Main
TARGET = run.out
SRC = $(wildcard $(SRC_FOLDER)*.cc)
OBJ = $(patsubst $(SRC_FOLDER)%.cc, $(OBJ_FOLDER)%.o, $(SRC))

EXE = $(BIN_FOLDER)run.out
EXE_ANALIZE = $(BIN_FOLDER)analisamem

all: execut 

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cc 
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

execut: $(OBJ)
	$(CC) $(CXXFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ)

clean:
	@rm -rf $(OBJ_FOLDER)* $(BIN_FOLDER)* out/media/* out/graph/*
