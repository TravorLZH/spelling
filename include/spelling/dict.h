#ifndef	DICT_H
#define	DICT_H
#include <spelling.h>
#include <stdio.h>
/* There will be at most 10000 words in the dictionary */
#define	DICT_WORDS	10000

extern struct word dict[DICT_WORDS];
extern int dicts;

extern int dict_init(char *filename);
extern int dict_check(char *word);
extern int dict_close(void);
extern int dict_add(char *word);

#endif
