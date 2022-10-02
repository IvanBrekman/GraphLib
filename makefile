# ====================================================================== Program =======================================================================
EXE_FILE = $(BIN)/kitty.purrrrr


cr: GraphLib ### While working on LIB ### 

	$(CC) main.cpp $(GraphLib_ObjectFile) $(GraphLib_CompileKeys) -o $(EXE_FILE)

	./$(EXE_FILE)
# ======================================================================================================================================================


# ====================================================================== GraphLib ======================================================================
CC 				:= g++

BIN				:= bin/

SRC_EXT			:= .cpp
OBJ_EXT			:= .obj.meow

SRC_FILES 	    := $(shell find */*$(SRC_EXT) 2>/dev/null)
OBJ_FILES		:= $(addprefix $(BIN), $(notdir $(SRC_FILES:$(SRC_EXT)=$(OBJ_EXT))))

INCLUDES		:= $(addprefix -I ,    $(shell find -type d -name "Class_*")) -I ../Class_Color
INCLUDES_INSIDE := $(addprefix -I ../, $(shell find -type d -name "Class_*"))
SFML_LIBS 		:= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

GraphLib_ObjectFile	 := $(BIN)GraphLib.lib
GraphLib_CompileKeys := $(INCLUDES) $(INCLUDES_INSIDE) $(SFML_LIBS)


GraphLib:
	clear
	
	$(shell python3 scripts/create_obj_files.py --cc=$(CC) --src_ext=$(SRC_EXT) --obj_ext=$(OBJ_EXT) $(SRC_FILES) $(OBJ_FILES))

	ar rvs $(GraphLib_ObjectFile) $(OBJ_FILES)

	rm $(OBJ_FILES)


GraphLib_clean:
	rm $(GraphLib_ObjectFile)
# ======================================================================================================================================================
