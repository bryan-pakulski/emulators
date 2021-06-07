# Library folder paths (to .so / .dll files)
MAINLIBFOLDER = lib
LIB := -L$(MAINLIBFOLDER)

# main include folder with headers
INCF := include
# Include subfolders
INC := -Iinclude -Iinclude/chip8 -Iinclude/SDL2 

# Libraries to include (by name)
LDFLAGS := lib/libSDL2-2.0.so.0

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
RUN := OFF
# Terminal to use + arguments
TERM := bash
TERMARGS := -c

# Compiler to be used
CC := g++
# Cflags to be used
CFLAGS := -std=c++11 -Wall -g3 $(INC) 

# Program name
EXECUTABLE := main
# Program arguments
EXECUTABLE_ARGUMENTS := bin/roms/PONG

# Source files & object generation
SOURCES := $(shell find $(SRC) -type f -name "*.cpp") $(shell find $(INCF) -type f -name "*.cpp") $(shell find $(SRC) -type f -name "*.c") $(shell find $(INCF) -type f -name "*.c")
OBJECTS := $(SOURCES:.cpp=.o)


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
	find $(SRC) -type f -name "*.o" -exec mv {} $(OBJ) \;
	find $(INCF) -type f -name "*.o" -exec mv {} $(OBJ) \;

	# Move binary file
	if [ -f $(EXECUTABLE) ]; then \
		mv $(EXECUTABLE) $(BIN)/$(EXECUTABLE); \
	fi

ifneq ("$(wildcard $(MAINLIBFOLDER))", "")
	if [ ! -d $(BIN)/lib/ ]; then \
		mkdir $(BIN)/lib/; \
	fi;
	cp $(MAINLIBFOLDER)/*.so* $(BIN)/lib/;
	cd $(BIN) && find lib/ -type f -name "*.so*" -exec patchelf $(EXECUTABLE) --add-needed {} \;
endif

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

# Run
run:
	$(TERM) $(TERMARGS) "./$(BIN)/$(EXECUTABLE) $(EXECUTABLE_ARGUMENTS)"

# Check for memory leaks
mem_check:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BIN)/$(EXECUTABLE) $(EXECUTABLE_ARGUMENTS)

# Cleanup
clean:
	rm -rf $(BIN)/$(EXECUTABLE)
	rm -rf $(OBJ)/*.o