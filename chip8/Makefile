#######################
### FOLDER SETTINGS ###
#######################

# Binary folder location
BIN := bin
# Source folder location
SRC := src
# Object folder location
OBJ := obj
# Static / Dynamic library folder location
LIB := lib
# Include folder for external libraries, check INCDEF to make sure subdirectories are included
INC := include

############################
### Include definitions  ###
############################

INCDEF := -I$(INC) -Iinclude/SDL2

######################
### COMPILER FLAGS ###
######################

# Compiler to be used, g++ only supported currently
CC := g++
CFLAGS := -std=c++17 -Wall -g3 $(INCDEF)

#########################
### EXECUTION OPTIONS ###
#########################

# Terminal to use + arguments
TERM := bash
TERMARGS := -c
# Program name
EXECUTABLE := main
# Program arguments
EXECUTABLE_ARGUMENTS := roms/PONG

####################
### Source files ###
####################

SOURCES := $(shell find $(SRC) -type f -name "*.cpp")

#################
### Libraries ###
#################

LIBRARIES := $(shell find $(LIB) -type f -name "*.so*") $(shell find $(LIB) -type f -name "*.a*")

#########################
### Object generation ###
#########################

OBJECTS := $(SOURCES:.cpp=.o)

# Generate objects based on source files
%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

###################
### Main target ###
###################

$(EXECUTABLE): $(OBJECTS)
	echo $(SOURCES)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE) -L$(LIB) $(LIBRARIES)

	# Move .o files if they exist
	find $(SRC) -type f -name "*.o" -exec mv {} $(OBJ)/  \;

	# Move binary file
	if [ -f $(EXECUTABLE) ]; then \
		mv $(EXECUTABLE) $(BIN)/$(EXECUTABLE); \
	fi

# copy any libraries to the binary release and link via patchelf if required
ifneq ("$(wildcard $(LIB))", "")
	if [ ! -d $(BIN)/lib/ ]; then \
		mkdir $(BIN)/lib/; \
	fi;
	find $(LIB) -type f -name "*.so*" -exec cp {} $(BIN)/lib/ \;
	cd $(BIN) && find lib/ -type f -name "*.so*" -exec patchelf $(EXECUTABLE) --add-needed {} \;
endif

##############
###	 Init  ###
##############
init:
	# Create binary folder if it doesn't exist
	if [ ! -d $(BIN) ]; then \
		mkdir $(BIN); \
	fi

	# Create obj folder if it doesn't exist
	if [ ! -d $(OBJ) ]; then \
		mkdir $(OBJ); \
	fi

	# Create source folder if it doesn't exist
	if [ ! -d $(SRC) ]; then \
		mkdir $(SRC); \
	fi

	# Create lib folder if it doesn't exist
	if [ ! -d $(LIB) ]; then \
		mkdir $(LIB); \
	fi

	# Create include folder if it doesn't exist
	if [ ! -d $(INC) ]; then \
		mkdir $(INC); \
	fi

###################
###  Run target  ##
###################
run:
	cd $(BIN); \
	$(TERM) $(TERMARGS) "./$(EXECUTABLE) $(EXECUTABLE_ARGUMENTS)"; \
	cd ..;

###################
###  Mem check  ###
###################
mem_check:
	cd $(BIN); \
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./$(EXECUTABLE) $(EXECUTABLE_ARGUMENTS); \
	cd ..;

####################
### Clean target ###
####################
clean:
	find $(BIN) -type f -name "$(EXECUTABLE)" -exec rm -f {} \;
	find $(BIN)/lib -type f -name "*" -exec rm -f {} \;
	find $(SRC) -type f -name "*.o" -exec rm -f {} \;
	find $(OBJ) -type f -name "*.o" -exec rm -f {} \;