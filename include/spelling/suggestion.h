#ifndef	SUGGESTION_H
#define	SUGGESTION_H
#include <spelling.h>

extern int similar(char *a,char *b);
extern int missing_one(char *a,char *b);
extern int provide_suggestions(char *word,struct word *suggestions,int max);
#endif
