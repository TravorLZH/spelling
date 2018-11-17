#include <spelling/dict.h>
#include <spelling/suggestion.h>
#include <string.h>

int similar(char *a,char *b)
{
	int i;
	int x=0;
	int len=strlen(a);
	for(i=0;i<len;i++){
		if(a[i]!=b[i]){
			/* If more than one mistake */
			if(++x>1){
				return 0;
			}
		}
	}
	return 1;
}

int one_missing(char *a,char *b)
{
	int i,j;
	int x=0;
	int len=strlen(a);
	for(i=0,j=0;i<len;i++){
		if(a[i]!=b[j]){
			/* Same as above */
			if(++x>1){
				return 0;
			}
		}else{
			j++;
		}
	}
	return 1;
}

int provide_suggestions(char *word,struct word *words,int max)
{
	int i,j=0,k=0;
	int len=strlen(word);
	int dlen;
	for(i=0;i<dicts;i++){
		if(j>=max){
			break;
		}
		dlen=strlen(dict[i].name);
		if(dlen==len&&similar(word,dict[i].name)){
			strcpy(words[j++].name,dict[i].name);
		}else if((len-dlen)==1&&one_missing(word,dict[i].name)){
			strcpy(words[j++].name,dict[i].name);
		}else if((len-dlen)==-1&&one_missing(dict[i].name,word)){
			strcpy(words[j++].name,dict[i].name);
		}
	}
	return j;
}
