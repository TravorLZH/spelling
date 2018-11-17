#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <spelling/dict.h>
#include <spelling/suggestion.h>

/* Input buffer */
char buf[BUFSIZ];
char outbuf[BUFSIZ];

/* Suggestion buffer */
struct word sug[10];

int app_print(const char *fmt,...)
{
	va_list vlist;
	va_start(vlist,fmt);
	vsprintf(outbuf,fmt,vlist);
	va_end(vlist);
	return printf(APPNAME ": %s\n",outbuf);
}

int do_word(char *word)
{
	char flag=0;
	int i,len;
	len=strlen(word);
	char tmp[len];
	/* Convert into lower cases */
	for(i=0;i<len;i++){
		tmp[i]=tolower(word[i]);
	}
	tmp[i]='\0';
	if(dict_check(tmp)<0){
		flag=1;
		len=provide_suggestions(tmp,sug,10);
		printf("%s: ",word);
		if(len==0){
			printf("Unknown word\nAdd to dictionary [y/n]");
			gets(buf);
			if(tolower(buf[0])=='y'){
				/* Add the word to the dictionary */
				dict_add(tmp);
			}
			return flag;
		}
		printf("Do you mean:");
		for(i=0;i<len;i++){
			printf("\t%d. %s",i+1,sug[i].name);
		}
		printf("\nOr add to dictionary [y/n]");
		gets(buf);
		if(tolower(buf[0])=='y'){
			dict_add(tmp);
		}
	}
	return flag;
}

int main(int argc,char **argv)
{
	int i,len,flag;
	char *tmp=NULL;
	dict_init(DICT_FILENAME);
	/* If there are words in the argument */
	if(argc>1){
		for(i=1;i<argc;i++){
			flag=do_word(argv[i]);
		}
		if(!flag){
			puts("No problem");
		}
		return 0;
	}
check_words:
	printf("> ");
	gets(buf);
	if(buf[0]=='#'){
		goto bye;
	}
	if(buf[0]=='!'){
		dict_delete(&buf[1]);
		goto check_words;
	}
	len=strlen(buf);
	tmp=strtok(buf," ");
	if(tmp==NULL){
		goto check_words;
	}
	do{
		do_word(tmp);
	}while((tmp=strtok(NULL," "))!=NULL);
	goto check_words;
bye:	dict_close();
	return 0;
}
