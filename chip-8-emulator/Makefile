MODE := C++
# Compiler to be used
CC := g++
# Library files
LIB := -Llib
# main include folder
INCF := include
# Include 
INC := -Iinclude -Iinclude/chip8 -Iinclude/SDL2
# Libraries to include
LDFLAGS := -l SDL2

# Cflags to be used
CFLAGS := -std=c++11 -Wall -g $(INC)

# Binary folder location
BIN := bin
# Source folder location
SRC := src
# Object folder location
OBJ := obj
# Tests folder location
TST := tests
# Documentation folder location
DOC := doc

# Run file after compilation?
RUN := ON
# Terminal to use + arguments
TERM := bash
TERMARGS := -c

# Program name
EXECUTABLE := main
# Program arguments
EXECUTABLE_ARGUMENTS := bin/roms/PONG

# Source files
SOURCES := $(shell find $(SRC) -type f -name "*.cpp") $(shell find $(INCF) -type f -name "*.cpp") $(shell find $(SRC) -type f -name "*.c") $(shell find $(INCF) -type f -name "*.c")

# Object generation
ifeq ($(MODE), C++)
	OBJECTS := $(SOURCES:.cpp=.o)
else
	OBJECTS := $(SOURCES:.c=.o)
endif


# Main target
$(EXECUTABLE): $(OBJECTS)
	echo $(SOURCES)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LIB) $(LDFLAGS)

	# Create binary folder if it doesn't exist
	if [ ! -d $(BIN) ]; then \
		mkdir $(BIN); \
	fi

	# Create obj folder if it doesn't exist
	if [ ! -d $(OBJ) ]; then \
		mkdir $(OBJ); \
	fi

	# Move .o files if they exist
	mv $(SRC)/*.o $(OBJ)/ || echo No .o files to move from $(SRC) directory
	find $(INCF) -type f -name "*.o" -exec mv {} $(OBJ)/  \;

	# Move binary file
	if [ -f $(EXECUTABLE) ]; then \
		mv $(EXECUTABLE) $(BIN)/$(EXECUTABLE); \
	fi

	# Run file if run is set to true
	# export DISPLAY=:0;\ (Windows fix for x)
	if [ "$(RUN)" = "ON" ]; then \
		$(TERM) $(TERMARGS) "./$(BIN)/$(EXECUTABLE) $(EXECUTABLE_ARGUMENTS)"; \
	fi

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CFLAGS) $< $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAFS) $< $(LDFLAGS) -o $@

# To run tests
test:
	echo "Running unit tests..."
	$(CC) $(CFLAGS) $(wildcard $(TST)/*.cpp) $(LDFLAGS) -o "$(EXECUTABLE)_test"
	mv "$(EXECUTABLE)_test" $(TST)
	$(TERM) $(TERMARGS) "./$(TST)/$(EXECUTABLE)_test $(EXECUTABLE_ARGUMENTS)"

mem_check:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BIN)/$(EXECUTABLE) $(EXECUTABLE_ARGUMENTS)

# Generate documentation
doc:
	doxygen Doxyfile

# To remove generated files
clean:
	rm -rf $(BIN)/$(EXECUTABLE)
	rm -rf $(OBJ)/*.o
	rm -rf $(SRC)/*.o
	#rm -rf $(DOC)/*
	rm -rf $(TST)/*.o
	find $(INCF) -type f -name "*.o" -exec rm -rf {} \;
	rm -rf $(TST)/$(EXECUTABLE)_test