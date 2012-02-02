/*   CS 136 (Winter 2011)
     Interface file for Assignment 6, Question 3
     lists.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "lists.h"
#include <stdbool.h>
#include <ctype.h>


struct node {
	int first;
	struct node *rest;
};



/*
	Purpose: Determines the length, ie the number of elements, of a list
	Pre:	 Input must be a valid list format, ie 
			 "( int ... int )" or "( )"
	Post:	 An integer >=0 that represents the number of items in the list
			 has been returned.
*/

int length(struct node *lst) {
	struct node *p;
	int num_elem = 0;
	for (p = lst; p!=NULL; p = p->rest) {
		num_elem++;
	}
	
	return num_elem;
}




/*
	Purpose: Determines whether a given list contains a specified element
	Pre:	 Input must be a valid list format, ie 
			 "( int int int ... int )" or "( )", and an integer
	Post:	 True/1 has been returned if the given list contains 
			 the specified element, False/0 has been returned if the 
			 element is not found or the list is empty/NULL
*/

bool contains(struct node *lst, int val) {
	struct node *p;
	for (p = lst; p!=NULL; p = p->rest) {
		if (p->first == val) {
			return true;
		}
	}
	
	return false;
}




/*
	Purpose: Appends two lists together into one list
	Pre:	 Inputs must be valid list formats, ie 
			 "( int int int ... int )" or "( )"
	Post:	 Returns either: -A copy of lst1 if lst2 is empty/NULL
							 -A copy of lst2 if lst1 is empty/NULL
							 -lst1, but with the last cons clause pointing to
							  the beginning of lst2, ie the two lists appended together
*/

struct node *append(struct node *lst1, struct node *lst2) {

	struct node *ans = NULL;
	struct node *prev;
	
	if (lst1 == NULL) {
		ans = copy_list(lst2);
		return ans;
	}
	if (lst2 == NULL) {
		ans = copy_list(lst1);
		return ans;
	}	
	
	ans = cons(lst1->first, NULL);
	prev = ans;
	lst1 = lst1->rest;
	
	
	while (lst1 != NULL) {
		prev->rest = cons(lst1->first, NULL);
		prev = prev->rest;
		lst1 = lst1->rest;
	}
	while (lst2 != NULL) {
		prev->rest = cons(lst2->first, NULL);
		prev = prev->rest;
		lst2 = lst2->rest;
	}
	
	return ans;
}




/*

	Purpose: Reads and returns a list from standard input
	Pre:	 Input must be of the form (int int ... int) with 
			 whitespaces anywhere before/after the brackets, and in between integers
	Post:	 Returns the given list as a properly formatted list
			 ie ( 22       00			1	9
			 			9	882       )
			 	-> ( 22 00 1 0 9 882 )

*/

struct node *read_list() {	
	
	//Skips the whitepsace, then gets the first ( out of the stream
	skip_whitespace();	
	getchar();
	skip_whitespace();
	
	//If the next character is ), then it's an empty list
	//So it returns NULL, which would be printed as "( )" by print_list
	if (peekchar() == ')'){
		getchar();
		return NULL;
	}	


	struct node *ans = NULL;
	struct node *prev;

	ans = cons(read_nat(), NULL);
	prev = ans;
	
	skip_whitespace();
	
	//Adds the character to the list until the end of the list, ), is read	
	while (peekchar() != ')') {
		prev->rest = cons(read_nat(), NULL);
		prev = prev->rest;
		skip_whitespace();
	}
	
	//This removes the last ) from the input stream, allowing you to read 
	//more than one list consecutively in the same program
	skip_whitespace();
	getchar();
	
	return ans;
}



/*
	Recursive versions of the above functions
*/

int length_R(struct node *lst) {

	if (lst == NULL) {
		return 0;
	} else return (1 + length_R(lst->rest));

	return 0;
}

bool contains_R(struct node *lst, int val) {
	if (lst == NULL) {
		return false;
	} else if (lst->first == val) {
		return true;
	} else return contains_R(lst->rest, val);
}

struct node *append_R(struct node *lst1, struct node *lst2) {
	if (lst1 == NULL && lst2 == NULL){
		struct node *nullnode = NULL;
		return nullnode;
	} else if (lst1 == NULL) {
		return cons(lst2->first, append_R(lst2->rest, NULL));
	} else return cons(lst1->first, append_R(lst1->rest, lst2));
}




/*
	Helper functions to work with lists, input, etc
*/

struct node *cons(int fst, struct node *rst) {
	struct node *new = malloc(sizeof(struct node));
	if (new == NULL) {
		printf("cons: out of memory\n");
		abort();
	}
	new->first = fst; /* same as (*new).first = fst */
	new->rest = rst;
	return new;
}



void free_list(struct node *lst) {
	struct node *p;
	while (lst != NULL) {
		p = lst->rest;
		free(lst);
		lst = p;
	}
}



void print_list(struct node *lst) {
	struct node *p;
	printf("( ");
	for (p = lst; p != NULL; p = p->rest)
		printf("%d ", p->first);
	printf(")\n");
}


struct node *copy_list(struct node *lst) {
	struct node *ans = NULL;
	struct node *prev;
	if (lst == NULL) return ans;
	ans = cons(lst->first, NULL);
	prev = ans;
	lst = lst->rest;
	
	while (lst != NULL) {
		prev->rest = cons(lst->first, NULL);
		prev = prev->rest;
		lst = lst->rest;
		}
	return ans;
}


int peekchar() {
	return ungetc(getchar(), stdin);
}

void skip_whitespace() {
	while (isspace(peekchar()))
		getchar();
}

bool has_next() {
	skip_whitespace();
	return (peekchar() != EOF);
}

int read_nat() {
	int nc, ans = 0;
	skip_whitespace();
	while (isdigit(peekchar())) {
		nc = getchar();
		ans = ans * 10 + nc - '0';
	}
	return ans;
}



