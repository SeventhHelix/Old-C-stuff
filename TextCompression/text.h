#include <stdbool.h>

struct hashtable {
	int size;	// size of hash table (i.e., length of table array)
	struct htElem **table; // array of htElem pointers
};

struct htElem {
	char *key;	//A reference to a single word
	int value;	//The code corresponding to this word
	struct htElem *next;
};

struct hashtable *htMake(int n);
bool htContains(struct hashtable *H, char *key);
int htGetValue(struct hashtable *H, char *key);
void htAddValue(struct hashtable *H, char *key, int value);
void htPrint(struct hashtable *H);
int hash(char *key, int n);
void htFree(struct hashtable *H);
void text_compress(struct hashtable *H);
void text_decompress();
