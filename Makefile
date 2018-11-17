# Makefile for Spelling
SOURCES=main.c dict.c suggestion.c
CPPFLAGS+=-Iinclude
CFLAGS+=-g
OBJ=$(SOURCES:.c=.o)

all:	spelling

spelling:	$(OBJ)
	$(CC) -o$@ $^

clean:
	rm -rf spelling
	rm -rf $(OBJ)
