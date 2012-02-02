#include	<stdlib.h>
#include	<stdio.h>
#include	<stdbool.h>
#include	"text.h"
#include	<string.h>
#include	<ctype.h>

// pre: n > 0.
// post: A reference to a hashtable structure is returned that
//		 its size field is n and its table field is an array
//		 of length n.
struct hashtable *htMake(int n){
	struct hashtable *H = malloc(sizeof(struct hashtable));

	H->size = n;
	H->table = malloc(n * sizeof(struct htElem));

	for ( int i=0; i<n; i++) {
		(H->table)[i] = NULL;
	}

	return H;
}

// pre: None.
// post: Returns true if and only if the hash table H contains
// 		 the word key.
bool htContains(struct hashtable *H, char *key){
	int hashval = hash(key, H->size);
	struct htElem *keychecker = (H->table)[hashval];
	while ( keychecker != NULL ) {
		if ( strcmp(keychecker->key, key) == 0 ) return true;
		keychecker = keychecker->next;
	}
	return false;	
}

// pre: htContains(H, key) == true.
// post: The numerical code corresponding to the word key in
//the hash table H is returned.
int htGetValue(struct hashtable *H, char *key){	
	int hashval = hash(key, H->size);
	struct htElem *keychecker = (H->table)[hashval];
	while ( keychecker != NULL ) {
		if ( strcmp(keychecker->key, key) == 0 ) return keychecker->value;
		keychecker = keychecker->next;
	}
	return 0;
}

// pre: htContains == false.
// post: The word key having numerical code value is added to
//the hash table H.
void htAddValue(struct hashtable *H, char *key, int value){
	int hashval = hash(key, H->size);	
	
	struct htElem *tempelem = (H->table)[hashval];
	struct htElem *newelem = malloc(sizeof(struct htElem));
			
	(H->table)[hashval] = newelem;
	newelem->key = malloc((strlen(key) + 1) * sizeof(char));
	
	strcpy(newelem->key, key);
	newelem->value = value;
	newelem->next = tempelem;
}

// pre: None.
// post: Prints n lines to standard output, one for each of the n
//		 elements in the hash table’s array. Each line consists of
//		 all of the key/value pairs that hash to the same value.
//		 Print with printf("[%s,%d] ", key, value).
void htPrint(struct hashtable *H){

	int i = 0;
	struct htElem *elemptr = (H->table)[i];	
	while( i < (H->size)) {
		elemptr = (H->table)[i];
		for ( int j=0; elemptr != NULL; j++) {
			printf("[%s,%d] ", elemptr->key, elemptr->value);
			elemptr = elemptr->next;
		}
		printf("\n");	
		i++;	
	}
}



// post: Returns the value of the hash function for the word key
//where n is the size of the hash table.
int hash(char *key, int n){
	int hashval = 0;	
	for (int i=0; key[i]!='\0';i++) {
		hashval += key[i];
	}
	hashval = hashval % n;
	return hashval;
}

// Purpose: Frees a hashtable
// Pre: True
// Post: The hashtable, and every htelement in its array have been freed
void htFree(struct hashtable *H){
	struct htElem *elemptr, *tmpelem;
	//Free each spot in the main H->table array
	for ( int i=0;i < (H->size); i++) {
		elemptr = (H->table)[i];
		while ( elemptr != NULL ) {
			tmpelem = elemptr;
			elemptr = elemptr->next;
			free(tmpelem->key);
			free(tmpelem);
		}
	}
	//Free the table under H, then H itself
	free(H->table);
	free(H);
}

//Standard read input functions
int peekchar() {
	return ungetc(getchar(), stdin);
}

// Purpose: Reads a string from input
// Pre: True
// Post: Returns a reference to a new malloced C-style string read from input
char *str_read() {
	int size = 1; // size of the array
	int next_index = 0; // where the next number goes
	char *str = malloc(size * sizeof(char));
	while (isalnum(peekchar()) && !(isspace(peekchar()))) {
		if (next_index == size) {
			size *= 2;
			str = realloc(str, size*sizeof(char));
			if (str == NULL) {
				abort(); // error
			}
		}
		str[next_index] = getchar();
		next_index++;
	}
	if (next_index == size) str = realloc(str, (size+1)*sizeof(char));	
	str[next_index] = '\0';
	return str;
	
}


// Purpose: Compresses a string read from input using a hashtable H to store
//          recurring words
// Pre:     The Hashtable H must be empty, with no pre-set elements
//				Otherwise the hashtable may contain keys/values that do not match
//				up with the text read from input
//			The First line of input must contain an integer value >=1 for the size of the hash table
//			Input should not contain any digits after the first line, and should not
//				include words with punctuation inside of them (such as can't and it's)
// Post:    Prints the compressed version of the read string to standard output
void text_compress(struct hashtable *H){
	char inch = peekchar();
	int wordctr = 0;	
	
	//Continues to read until the EOF is found
	while ( inch != EOF ) {
		if (inch == '\n') {								//If the gotten character is \n, print \n
			printf("\n");
			inch = getchar();
		}
		else if (isspace(inch) || ispunct(inch)) {		//If its a space or punctuation, 
			printf("%c", inch);							//then just print the char again
			inch = getchar();
		}
		else {											//Otherwise first read the string from input
			char *newword = str_read();					//Then if the word is already in the hashtable,
			if (htContains(H, newword)) {				//print the according value then free the read word
				printf("%d", htGetValue(H, newword));
				free(newword);
			}
			else {										//Otherwise add the value to the hashtable
				htAddValue(H, newword, wordctr);		//And print it
				printf("%s", newword);
				wordctr++;
				free(newword);
			}
		}
		inch = peekchar();
	}
}

// Purpose: Decompresses text read from standard input to readable text
// Pre: Each integer value in input must correspond to a valid word
//			ie. Each integer in input must be less than 
//			the number of words before the integer
//		The first token of input cannot be an integer
// Post: The readable, decompressed version of the text read from input
//		 is printed out to standard output
void text_decompress() {
	
	//Creates a new array of pointer to chars to hold the strings
	char **strdict = malloc(sizeof(char*));	
	strdict[0] = NULL;
	
	char inch = peekchar();
	int wordctr = 0;
	
	//Loops while the current character being worked on is not EOF
	while ( inch != EOF ) {
		if (inch == '\n') {					//If the gotten character is \n, print \n
			printf("\n");
			inch = getchar();
		}
		else if (isspace(inch) || ispunct(inch)) {		//If its a space or punctuation, 
			printf("%c", inch);							//then just print the char again
			inch = getchar();
		}	
		else if ( isalpha(inch) ) {				//If the character is an alpha char
			char *newword = str_read();			//Read the full word
			strdict[wordctr] = newword;			//Add it to the dictionary
			wordctr++;							//Increment the number of words
			
			//Increase the memory size of strdict by one (since wordctr is increased by one)
			strdict = realloc(strdict, sizeof(char*) * (wordctr+1));	
			printf("%s", newword);					//Print the word
		} else {
			char *newword = str_read();				//Otherwise the word is a digit
			printf("%s", strdict[atoi(newword)]);	//Pass the converted integer version
			free(newword);							//Of the read word and print the 
		}											//string located at that index, then free the word
		inch = peekchar();	//peeks at the next character for usage in the next lop
	}
	
	//Frees the new array
	for (int i=0; i<wordctr; i++) {
		free(strdict[i]);
	}
	free(strdict);
	
}

