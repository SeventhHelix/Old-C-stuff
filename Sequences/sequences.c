//
//	CS 136 - Winter 2011
//	Name:	Jeff Dyck
//	ID#:	20370778
//	UserID:	j6dyck
//	Assignment:	10
//	Problem:	1 - sequences.c
//

#include "sequences.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>


/*
	Purpose: Calculates the number of digits in an integer
	Pre: Num must be an integer
	Post: Returns the number of digits in the integer num
*/
int int_digits(int num) {
	int digits = 0;
	int div_num = num;
	while (div_num != 0) {
		div_num /= 10;
		digits++;
	}
	return digits;
}

/*
	Purpose: Converts an integer to a string
	Pre: Num must be an integer
	Purpose: Returns a reference to a new string that contains the
			 converted integer
*/
char *int_to_string(int num) {
	char *intstr = malloc(sizeof(char) * (int_digits(num)+1));
	sprintf(intstr,"%d",num);
	return intstr;
}


/*
	Purpose: Consumes a character sequence, seq, and creates a new
			 string that represents a compressed version of the original
			 sequence to save space in memory.
	Pre: The consumed string must be a sequence. ie, every character must be an upper-case letter
	Post: Returns a reference to a new string on the heap representing the
		  compressed version of the consumed sequence
	Parameters: char *seq: A pointer to a character sequence that is
							to be compressed
*/

char *sequence_compress(char *seq) {
	
	if (seq[0] == '\0') {
		char *comp = malloc(sizeof(char));
		comp[0] = '\0';
		return comp;
	}
	
	//Creates the new sequence the size of seq
	char *comp = malloc(sizeof(char) * (strlen(seq) + 1));
	
	//Used to store the position being used in comp
	int comp_pos = 0;
	
	//Stores the number of reccurences of the same letter
	int num_rec = 0;
	
	//The number of indeces in comp (used to realloc)
	int comp_ind = 0;
	
	//Used for the main while loop
	int i = 0;
	
	//Makes two inital checks. If the second or third character is
	// '\0' then no compression can be done, so it sets the characters
	//and returns the new string
	if (seq[1] == '\0') {
		comp[0] = seq[0];
		comp[1] = '\0';
		return comp;
	} else if (seq[2] == '\0') {
		comp[0] = seq[0];
		comp[1] = seq[1];
		comp[2] = seq[2];
		return comp;
	}
	
	//If the string is longer than this, then it may begin the 
	//full loop to compress the sequence
	while(seq[i] != '\0') {
		//Saves the number of recurrences of the current letter
		//being checked in seq
		num_rec = check_recur(seq, i);
		
		//If the letter is by itself
		if (num_rec == 0) {
			comp[comp_pos] = seq[i];
			comp_pos++;
			comp_ind++;
			i++;
		//If there are two letters side by side
		} else if (num_rec == 2) {
			comp_ind += 2;
			comp[comp_pos] = seq[i];
			comp[comp_pos+1] = seq[i+1];
			comp_pos += 2;
			i += 2;
		//Otherwise there are >=3 letters beside eachother
		} else {
			//Creates the string containing the number of recurrences
			char *rec_str = int_to_string(num_rec);
			int j=0;
			//Adds the integer to the comp string
			while(rec_str[j] != '\0') {
				comp[comp_pos+j] = rec_str[j];
				j++;
			}
			comp_ind += (int_digits(num_rec)+1);
			comp[comp_pos+j] = seq[i+1];
			comp_pos += (int_digits(num_rec))+1;
			i += num_rec;
			//Frees the rec_str before the loop ends
			free(rec_str);
		}

	}
	
	//Sets the last character to '\0' and reallocs the main comp
	//string to get rid of the extra space
	comp[comp_ind] = '\0';
	comp = realloc(comp, sizeof(char)*(strlen(comp)+1));

	return comp;
}

/*
	Purpose: Consumes a sequence and a position, and returns the number
			 to be used in the compressed sequence. It returns 0 if the
			 next letter is different or the next-after character is different,
			 otherwise returns the number of characters the same as the 
			 character at the specified position in the sequence.
			 ie: 'ABC' -> 0		'AAB' -> 0	'AAA' -> 3
	Pre: The consumed sequence must, of course, abide by the definition of a
		 sequence, and pos must be a valid index of seq
	Post: Returns an integer that is used in the compressed sequence to
		  represent recurring characters.
*/

int check_recur(char *seq, int pos){
	int recur = 1;
	
	//Increments recur until the end of the sequence is reached or
	//the characters do not match
	for (int i=1; seq[i+pos] != '\0' && seq[i+pos] == seq[pos]; i++) {
		recur++;
	}
	
	//If recur is less than two, then we have the case of
	//something like 'ABC' so just return 0
	if (recur < 2) return 0;
	
	//Otherwise, it will return recur
	return recur;
}


/*
	Purpose: Consumes a compressed character sequence, compressed, and creates a new
			 string that represents a decompressed version of the original
			 sequence for the user to read.
	Pre: The consumed string, must consist of only upper-case letters and integers
	Post: Returns a reference to a new string on the heap representing the
		  decompressed version of the consumed sequence
	Parameters: char *compressed: A pointer to a character sequence that is
							to be decompressed
*/


char *sequence_decompress(char *compressed) {

	//Creates a temp string, a copy of compressed, that allows us
	//to manipulate the data in compressed
	char *temp_str = malloc(sizeof(char)*(strlen(compressed)+1));
	strcpy(temp_str, compressed);
	
	
	//mem_size is the initial size of the new string. This will be incremented
	//as it goes through the loop
	int mem_size = 1;	
	int i = 0;
	
	while(temp_str[i] != '\0') {
		//Loops through temp_str until it finds a non-alpha character
		while (isalpha(temp_str[i])) {
			//Sets the characters to 0, so atoi ignores them and will return
			//the number that follows (ie atoi("00000012CAT") -> 12)
			temp_str[i] = '0';
			i++;
			mem_size++;
		}
		//Adds the next integer to the amt of memory needed
		//ie 12A needs 12 blocks of memory
		mem_size += atoi(temp_str);
		
		//Sets the digits to 0, again so atoi ignores them
		while (isdigit(temp_str[i])) {
			temp_str[i] = '0';
			i++;
		}
		
		//If a letter follows an integer, then set them to 0
		//Note that this doesn't increment mem_size since the char
		//after an integer is just to indicate which letter will be used
		if (isalpha(temp_str[i])) {
			temp_str[i] = '0';
			i++;
		}
	}
	
	//Creates the new string based on the calculated mem_size
	char *decomp = malloc(sizeof(char) * mem_size);

	//Re-copies compressed to temp_str so we can work with it again
	strcpy(temp_str, compressed);

	int j = 0;
	int decomp_ind = 0;
	
	//How many times a character recurs
	int num_chars = 0;
	//Which char will be put into comp next
	char next_char;
	
	while (temp_str[j] != '\0') {
	
		//If the current char is an integer
		if (isdigit(temp_str[j])) {
			
			//num_chars determines how many of the next char we need to decompress
			num_chars = atoi(temp_str);
			while (isdigit(temp_str[j])) {
				temp_str[j] = '0';
				j++;
			}
			next_char = temp_str[j];
			//Sets decomp[decomp_ind] to the specified char until num_chars is 0
			//ie 5A sets 5 spots in decomp to A
			while (num_chars != 0) {
				decomp[decomp_ind] = next_char;
				decomp_ind++;
				num_chars--;
			}
			
			temp_str[j] = '0';
			j++;
		}
		
		while (isalpha(temp_str[j])) {
			decomp[decomp_ind] = temp_str[j];
			temp_str[j] = '0';
			j++;
			decomp_ind++;
		}
	}
	
	//Sets the last char to the null character
	decomp[decomp_ind] = '\0';
	
	//Frees temp_str, since it is not used anymore
	free(temp_str);
	return decomp;

}


