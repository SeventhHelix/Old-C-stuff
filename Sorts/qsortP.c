//
//	CS 136 - Winter 2011
//	Name:	Jeff Dyck
//	ID#:	20370778
//	UserID:	j6dyck
//	Assignment:	9
//	Problem:	2 - qsortP.c
//

#include <stdio.h>
#include "qsortP.h"
#include <assert.h>


void swapVals (int *a, int i1, int i2) {
	int temp = *(a+i1);
	*(a+i1) = *(a+i2);
	*(a+i2) = temp;
}

void qsort(int *a, int len) {
	if (len > 0) {
		int pivot = partition(a, len);
		qsort(a, pivot);
		qsort((a+pivot+1), len-pivot-1);
	}
}


void printArray (int *a, int n) {
	for(int i=0; i<n; i++) {
		printf("%d ", *(a+i));
	}
	printf("\n");
	return;
}


void quicksort (int *a, int len) {
	qsort(a, len);
	return;
}



int partition(int *a, int len) {

	int ind1 = 0;
	int ind2 = (len - 2);
	int pivot = len / 2;

	//Orients the left, right, and pivot elements
	if (*a >= *(a+pivot) && *a >= *(a+len-1)) 
		swapVals(a, 0, len-1);
	else if (*(a+pivot) >= *a && *(a+pivot) >= *(a+len-1)) 
		swapVals(a, pivot, len-1);
	if (*a >= *(a+pivot)) 
		swapVals(a, 0, pivot);
		
	//Double checks that left <= pivot <= right
	assert(*a <= *(a+len-1));
	assert(*(a+pivot) <= *(a+len-1));
	
	//If the array only has 3 elements, then return
	if (len <= 3) 
		return pivot;

	//Otherwise, it puts the pivot element at the end and changes pivot
	//to pivot-1, since the pivot point has moved out of the way
	swapVals(a, pivot, (len-2));
	pivot = (len-2);
	
	do {
		//Make sure that a at ind2 is <= a at ind1, then swaps them
		if (*(a+ind1) >= *(a+pivot) && *(a+ind2) <= *(a+pivot)) {
			assert(*(a+ind2) <= *(a+ind1));
			swapVals(a,ind1,ind2);
		}

		if (*(a+ind1) <= *(a+pivot))
			ind1++;
		if (*(a+ind2) >= *(a+pivot))
			ind2--;
	} while (ind1 <= ind2);
	
	swapVals(a,ind1,pivot);
	
	int temp2 = pivot;
	pivot = ind1;
	ind1 = temp2;
	
	//Makes sure that pivot is in the right spot
	assert(*(a+pivot) >= *(a+pivot-1) && *(a+pivot) <= *(a+pivot+1));
	
	return pivot;
}

