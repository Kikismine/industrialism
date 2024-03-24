UNAME_S = $(shell uname -s) # device type

CPP = clang++
CFLAGS = -std=c++20 --debug -g -Wall -Wextra -Wpedantic -Wstrict-aliasing -Weffc++
CFLAGS += -Wno-pointer-arith -Wno-newline-eof -Wno-unused-parameter -Wno-gnu-statement-expression
CFLAGS += -Wno-gnu-compound-literal-initializer -Wno-gnu-zero-variadic-macro-arguments
CFLAGS += -Ilib/glm -Ilib/glfw/include -fbracket-depth=1024

LDFLAGS = lib/glfw/src/libglfw3.a -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

# GLFW required frameworks on OSX
ifeq ($(UNAME_S), Darwin)
	LDFLAGS += -framework Vulkan -framework IOKit -framework CoreVideo -framework Cocoa
endif

SRC = $(wildcard src/**/*.cpp) $(wildcard src/*.cpp) $(wildcard src/**/**/*.cpp) $(wildcard src/**/**/**/*.cpp)
OBJ  = $(SRC:.cpp=.o)
BIN = bin

.PHONY: all clean

all: dirs libs game

runc: run clean

libs:
	cd lib/glm && cmake . && make
	cd lib/glfw && cmake . && make

dirs:
	mkdir -p ./$(BIN)

run: all
	$(BIN)/game

game: $(OBJ)
	$(CPP) -o $(BIN)/game $^ $(LDFLAGS)

%.o: %.cpp
	$(CPP) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)

cleancmp:
	find . -type f -name '*.o' -delete

hml:
	find src/ | xargs wc -l

