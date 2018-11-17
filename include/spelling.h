#ifndef	SPELLING_H
#define	SPELLING_H

#define	APPNAME		"spelling"
/* Each one contains 31 characters at most (without NULL-terminator) */
#define	WORD_LENGTH	32
/* File name of dictionary */
#define	DICT_FILENAME	"dict.txt"

struct word {
	char name[WORD_LENGTH];
};

extern int app_print(const char *msg,...);
#endif
