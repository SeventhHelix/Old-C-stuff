//
//	CS 136 - Winter 2011
//	Name:	Jeff Dyck
//	ID#:	20370778
//	UserID:	j6dyck
//	Assignment:	9
//	Problem:	3 - strings.c
//

#include <stdio.h>
#include <stdlib.h>
#include "strings.h"

struct string *strNew(char *s) {
	int length = 0;
	
	//Calculates the length of the string
	for (int i=0; s[i]!='\0'; i++) {
		length++;
	}

	struct string *strstru = malloc(sizeof(int) + sizeof(char*));
	
	strstru->len = length;
	strstru->str = malloc(sizeof(char)*(length+1));
	
	//Goes through, copying the characters from s to strstru->str
	int ii = 0;
	while(s[ii]!='\0') {
		strstru->str[ii] = s[ii];
		ii++;
	}
	strstru->str[ii] = '\0';
	
	return strstru;
}


struct string *strRead() {
	char buf[256];
	scanf("%255s", buf);
	return strNew(buf);
}


struct string *strCpy(struct string *dst, struct string *src) {
	int i = 0;
	
	//Reallocates the memory of dst to the size of src+1
	dst->str = realloc(dst->str, sizeof(char)*(src->len+1));	

	//Copies over the characters from dst to src
	while (src->str[i] != '\0') {
		dst->str[i] = src->str[i];
		i++;
	}
	
	//Adds the \0 character, then sets the length
	dst->str[i] = '\0';
	dst->len = src->len;
	return dst;	
}


int strCmp(struct string *s1, struct string *s2) {

	//Goes through the letters in each string until one of them
	//reaches the \0 char
	for (int i=0; s1->str[i] != '\0' && s2->str[i] != '\0'; i++) {
		if (s1->str[i] < s2->str[i])
			return -1;
		if (s1->str[i] > s2->str[i])
			return 1;
	}
	
	//If it's gotten to this point, then one string is a substring of the other,
	//so whichever word is longer is larger, and it returns 
	if (s1->len < s2->len)
		return -1;
	else if (s1->len > s2->len)
		return 1;
	
	//If it gets through the first loop without returning, and the
	//lengths are equal, then they are the same word
	return 0;
}


struct string *strAppend(struct string *s1, struct string *s2) {
	
	//Sets the total length to the sum of the lengths of s1 and s2
	int length = s1->len + s2->len;

	struct string *appstr = malloc(sizeof(int) + sizeof(char*));
	
	//Sets the length and memory sizes according to length
	appstr->len = length;
	appstr->str = malloc(sizeof(char)*(length+1));
	
	//First goes through and copies characters from s1 to appstr
	int i = 0;
	while(s1->str[i]!='\0') {
		appstr->str[i] = s1->str[i];
		i++;
	}
	
	//Resets i to 0, and continues copying from s2
	i=0;
	while(s2->str[i]!='\0') {
		appstr->str[s1->len+i] = s2->str[i];
		i++;
	}
	
	//Adds the \0 char
	appstr->str[s1->len+i] = '\0';
	
	return appstr;
}

/*
	Checks to see if pat is a substring of text
	By checking each character starting at pos
*/
int isSubStr(char *text, char *pat, int pos){
	int i=0;
	
	//Loops while neither pat or text (starting at the desired position)
	//have reached the end char \0
	while (text[pos+i] != '\0' && pat[i] != '\0') {
		
		//If the chars are unequal, then it is not a substring
		//Returns 0, ie false
		if (text[i+pos] != pat[i])
			return 0;
		i++;
	}
	
	//If it was text that reached the end, then pat cannot be a substring
	//So returns 0, ie false
	if (text[i+pos] == '\0' && pat[i] != '\0')
		return 0;

	//Otherwise, there are no indications that pat is not a substring
	//of text, so it returns 1, ie true
	return 1;
}

struct string *strReplace(struct string *text, struct string *pat, struct string *repl) {
	
	//Used to remember the position of the array in the new string
	int replcountr = 0;
	int j = 0;
	struct string *replstr = malloc(sizeof(int) + sizeof(char*));
	replstr->len = 0;
	//This is the biggest that the string will need to be
	//Since the most extreme case is if every character in
	//text is replaced by pat
	//ie. strReplace("aaa","a","xyz") -> xyzxyzxyz (3x3 or 9 chars long)
	replstr->str = malloc(sizeof(int)*(text->len+1)*(pat->len+1));
	
	//Loops through every char in text until the end char \0
	for (int i=0; text->str[i] != '\0'; i++) {
	
		//If pat is a substring of the current spot in text
		if (isSubStr(text->str, pat->str, i)) {
		
			//Places the proper characters from repl into replstr
			while(repl->str[j] != '\0') {
				replstr->str[replcountr] = repl->str[j];
				replcountr++;
				replstr->len += 1;
				j++;
			}

			replstr->str[replcountr] = repl->str[j];
			j = 0;
			
			//Skips pat->len-1 characters in the main for loop
			//since we don't need to check the rest of the pattern
			//that was just replaced
			i += pat->len - 1;
			
		//Otherwise, it is not a substring, so just copy over the
		//character from text
		} else {
			replstr->str[replcountr] = text->str[i];
			replcountr++;
			replstr->len++;
		}

		
	}
	
	replstr->str[replcountr] = '\0';
	
	return replstr;
}


void strFree(struct string *s) {
	free(s->str);
	free(s);
}


























