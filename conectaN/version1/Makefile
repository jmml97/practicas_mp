SRC = src
INC = includes
OBJ = obj
BIN = bin

CXX = g++
CXXFLAGS =  -Wall -Wextra -pedantic -std=c++03 -g  -I$(INC)

# ************ All ***********************

all : $(OBJ) $(BIN) conectaN

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Compilación de módulos ************

$(OBJ)/matriz.o : $(SRC)/matriz.cpp $(INC)/matriz.hpp
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)/matriz.o $(SRC)/matriz.cpp
$(OBJ)/tablero.o : $(SRC)/tablero.cpp $(INC)/tablero.hpp $(INC)/matriz.hpp
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)/tablero.o $(SRC)/tablero.cpp
$(OBJ)/jugador.o : $(SRC)/jugador.cpp $(INC)/jugador.hpp
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)/jugador.o $(SRC)/jugador.cpp
$(OBJ)/conectaN.o : $(SRC)/conectaN.cpp $(INC)/jugador.hpp $(INC)/tablero.hpp
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)/conectaN.o $(SRC)/conectaN.cpp

conectaN: $(OBJ)/conectaN.o $(OBJ)/jugador.o $(OBJ)/matriz.o $(OBJ)/tablero.o
	$(CXX) -g -o $(BIN)/conectaN $(OBJ)/conectaN.o $(OBJ)/jugador.o $(OBJ)/matriz.o $(OBJ)/tablero.o


# ***********Creación de directorios************

$(OBJ):
	mkdir obj

$(BIN):
	mkdir bin


# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
