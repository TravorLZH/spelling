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

### Dependencies
main.o:	main.c include/spelling.h include/spelling/suggestion.h \
	include/spelling/dict.h
dict.o:	dict.c include/spelling.h include/spelling/dict.h
suggestion.o:	suggestion.c include/spelling.h include/spelling/suggestion.h
