CC = gcc

CFLAGS  = -std=c11 -O2 -g -Wall -Wextra -Wpedantic
CFLAGS += -Ilib/glfw/include
CFLAGS += -Ilib/glad/include
CFLAGS += -Ilib/stb
CFLAGS += -Ilib/cglm/include

LDFLAGS  = -Llib/glfw/src
LDFLAGS += -Llib/cglm
LDFLAGS += -lglfw -lGL -lcglm -lm

STB_O  	= lib/stb/stb_image.o
GLFW_A 	= lib/glfw/src/libglfw3.a
GLAD_O 	= lib/glad/src/glad.o
CGLM_A 	= lib/cglm/libcglm.a

SRC = $(wildcard src/**/*.c) $(wildcard src/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)
OBJ = $(SRC:.c=.o) $(GLAD_O) $(STB_O)
BIN = bin


.PHONY: all clean dirs libs run game

all: dirs libs game

libs: $(GLFW_A) $(GLAD_O) $(STB_O) $(CGLM_A)

$(STB_O): lib/stb/stb_image.c
	$(CC) $(CFLAGS) -o $@ -c $<
$(CGLM_A):
	cd lib/cglm && cmake -DCGLM_STATIC=ON . && make
$(GLFW_A):
	cd lib/glfw && cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF . && make
$(GLAD_O): lib/glad/src/glad.c
	gcc -o $@ -Ilib/glad/include -c $<

dirs:
	mkdir -p ./$(BIN)

run: all
	$(BIN)/game

game: $(OBJ)
	$(CC) -o $(BIN)/game $^ $(LDFLAGS)
	./$(BIN)/game

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf compile_commands.json $(BIN) $(OBJ)
