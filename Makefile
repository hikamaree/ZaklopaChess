SRC_DIR=src
LIB_DIR=lib
BUILD_DIR=build
BINARY=build/zaklopachess

CXX=gcc
GDB=gdb
MKDIR=mkdir -p
RM=rm -rf

LDFLAGS=-lraylib -lm
CXXFLAGS=-Wall -I $(LIB_DIR) -O3

SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJECTS=$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

WEB_DIR=web
OUT_HTML=game.html
IN_HTML=template.html
RAYLIB_SRC=raylib/src
LIBRAYLIB_A=$(RAYLIB_SRC)/libraylib.a

.PHONY: all run clean web
all: compile

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BINARY): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

compile:
	$(MKDIR) $(BUILD_DIR)
	$(MAKE) $(BINARY)

run: compile
	./$(BINARY)

clean:
	$(RM) $(BINARY) $(BUILD_DIR) $(WEB_DIR)

web:
	mkdir -p $(WEB_DIR)
	emcc --preload-file assets -s ALLOW_MEMORY_GROWTH=1 --no-heap-copy -s EXPORTED_RUNTIME_METHODS=ccall -o $(WEB_DIR)/$(OUT_HTML) $(SOURCES) -Wall -I$(LIB_DIR) $(LIBRAYLIB_A) -I$(RAYLIB_SRC) -L$(RAYLIB_SRC) -Os -s USE_GLFW=3 -sGL_ENABLE_GET_PROC_ADDRESS -s ASYNCIFY --shell-file $(IN_HTML) -DPLATFORM_WEB 
