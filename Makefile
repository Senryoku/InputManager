CXX = g++
OBJ = obj/
SRC = src/
BIN = bin/
POINTCPP = $(wildcard $(SRC)*.cpp) 
POINTOP := $(POINTCPP:.cpp=.o)
POINTO = $(patsubst src/%,$(OBJ)%,$(POINTOP)) #$(POINTOP:src=obj)

ifeq ($(SHELL), sh.exe) 
OS := Win
else
OS := $(shell uname)
endif

ifeq ($(OS), Linux)
RM = rm
LIBS := -lsfml-window -lsfml-system
endif
ifeq ($(OS), Darwin)
RM = rm
LIBS := -framework sfml-system -framework sfml-window
endif
ifeq ($(OS), Win)
RM = del
LIBS := -lsfml-window -lsfml-system
endif


all : dirs Test 

dirs :
dirs : 
ifeq ($(OS), Darwin)
	@./configure.sh bin obj src
endif
ifeq ($(OS), Linux)
	@./configure.sh bin obj src
endif
	
ifeq ($(OS), Win)
	@echo "Créer les dossiers bin/ et obj/ manuellement"
endif
.PHONY : dirs


OPT := -Wall -pedantic -O2

$(OBJ)%.o : $(SRC)%.cpp
	@echo Compilation du fichier $^
	@$(CXX) $(OPT) $^ -c -o $@
	
$(OBJ)IniFile.o : ../SimpleIniParser/src/IniFile.cpp
	@echo Compilation du fichier $^
	@$(CXX) $(OPT) $^ -c -o $@

Test : $(POINTO) $(OBJ)IniFile.o
	@echo "Edition des liens pour $@"
	@$(CXX) $(OPT) $^ -o $(BIN)Test $(LIBS)
ifeq ($(OS), Win)
	bin\Test.exe
endif

valgrind : Test
	valgrind -v --leak-check=full --tool=memcheck ./bin/Test