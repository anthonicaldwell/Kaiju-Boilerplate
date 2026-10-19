BINARY_NAME			= boilerplate.bin
COMPILER			= g++

DIR_BIN				= ../Binary/
DIR_SRC				= ../Source/
DIR_OBJ				= Object/

SOURCES				= $(shell find $(DIR_SRC) -type f -name "*.cpp")
OBJECTS				= $(patsubst $(DIR_SRC)%.cpp, $(DIR_OBJ)%.o, $(SOURCES))

FLAGS_LINK			= $(shell pkg-config --libs sdl2 glew) -lGL
FLAGS_COMPILE		= -std=c++20 -I$(DIR_SRC) $(shell pkg-config --cflags sdl2 glew)

all: $(DIR_BIN)$(BINARY_NAME)

$(DIR_BIN)$(BINARY_NAME): $(OBJECTS)
	@mkdir -p $(DIR_BIN)
	$(COMPILER) $^ $(FLAGS_LINK) -o $@
	@chmod +x $(DIR_BIN)$(BINARY_NAME)

# Pattern rule matches subdirectories recursively using %
$(DIR_OBJ)%.o: $(DIR_SRC)%.cpp
	@mkdir -p $(dir $@)
	$(COMPILER) $(FLAGS_COMPILE) -c $< -o $@

.PHONY: all clean

clean:
	rm -rf $(DIR_OBJ) $(DIR_BIN)$(BINARY_NAME)