CC = gcc 
CF = -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes \
     -Wdeclaration-after-statement -Wmissing-declarations \
     -Wimplicit-function-declaration -std=c99 -pedantic \
     -Wshadow -Wdouble-promotion -Wconversion -Wformat \
     -Wformat-signedness -Wformat-extra-args \
     -Wpointer-arith -Wcast-qual
LF = -lSDL2main -lSDL2 
DF = -DDEBUG_MODE
INC = -Iinclude
SRC = $(wildcard src/*.c)

all: $(SC)
	$(CC) -fsanitize=address -g $(CF) $(INC) $(SRC) $(DF) $(LF)
