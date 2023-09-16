CC = gcc 
CF = -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes \
     -Wdeclaration-after-statement -Wmissing-declarations \
     -Wimplicit-function-declaration -std=c99 -pedantic \
     -Wshadow -Wdouble-promotion -Wconversion -Wformat \
     -Wformat-signedness -Wformat-extra-args \
     -Wpointer-arith -Wcast-qual
LF = -lSDL2main -lSDL2 -lSDL2_image -ldl -lGL
DF = -DDEBUG_MODE
INC = -Iinclude -Ilib/glad/include/
SRC = $(wildcard src/*.c) $(wildcard lib/glad/src/*.c)

all: $(SC)
	$(CC) -g $(CF) $(INC) $(SRC) $(DF) $(LF) 
