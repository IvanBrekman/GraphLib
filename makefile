BIN			= bin
OUT_FILE	= cat.exe.purrrrr
OBJ_FILE	= kitty.obj.meow

OBJ			= $(BIN)/$(OBJ_FILE)
EXE			= $(BIN)/$(OUT_FILE)

SFML_LIBS 	= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

cr:
	clear

	g++ -c main.cpp -o $(OBJ)
	g++ $(OBJ) -o $(EXE) $(SFML_LIBS)

	./$(EXE)
