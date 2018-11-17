#include <string.h>
#include <stdlib.h>
#include <spelling/dict.h>

/* Dictionary */
struct word dict[DICT_WORDS];
/* The logical length for dictionary */
int dicts=0;

static char filename[FILENAME_MAX];

int dict_init(char *f)
{
	strncpy(filename,f,FILENAME_MAX);
	char buf[WORD_LENGTH];
	FILE *file=fopen(filename,"r");
	if(file==NULL){
		app_print("Dictionary `%s' not found, creating...",filename);
		if((file=fopen(filename,"w"))==NULL){
			perror(filename);
			exit(1);
		}
		goto bye;
	}
scan_dict:
	if(dicts>DICT_WORDS){
		goto bye;
	}
	fscanf(file,"%s",buf);
	if(buf[0]!='#'){
		strcpy(dict[dicts++].name,buf);
		goto scan_dict;
	}
bye:
	fclose(file);
	return 0;
}

int dict_check(char *word)
{
	int i;
	for(i=0;i<dicts;i++){
		if(!strcmp(dict[i].name,word)){
			return 1;
		}
	}
	return 0;
}


int dict_close(void)
{
	int i;
	FILE *file=fopen(filename,"w");
	if(file==NULL){
		perror(filename);
		exit(1);
	}
	for(i=0;i<dicts;i++){
		fprintf(file,"%s\n",dict[i].name);
	}
	fprintf(file,"#\n");
	fflush(file);
	fclose(file);
	return 0;
}

int dict_add(char *word)
{
	if(dicts<DICT_WORDS){
		strcpy(dict[dicts++].name,word);
		return 0;
	}
	return 1;
}
