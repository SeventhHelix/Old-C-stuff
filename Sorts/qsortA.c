//
//	CS 136 - Winter 2011
//	Name:	Jeff Dyck
//	ID#:	20370778
//	UserID:	j6dyck
//	Assignment:	9
//	Problem:	1 - qsortA.c
//

#include <stdio.h>
#include "qsortA.h"
#include <assert.h>


void swapVals (int a[], int i1, int i2) {
	int temp = a[i1];
	a[i1] = a[i2];
	a[i2] = temp;
}


// qsort the numbers in array a between index
// left (included) and right (also included)
void qsort(int a[], int left, int right) {
	if (left < right) {
		int mid = partition(a, left, right);
		qsort(a, left, mid-1);
		qsort(a, mid+1, right);
	}
}


int partition(int a[], int left, int right) {

	int ind1 = left;
	int ind2 = (right - 1);
	int pivot = (left + right) / 2;

	//Orients the left, right, and pivot elements
	if (a[left] >= a[pivot] && a[left] >= a[right]) 
		swapVals(a, left, right);
	else if (a[pivot] >= a[left] && a[pivot] >= a[right]) 
		swapVals(a, pivot, right);
	if (a[left] >= a[pivot]) 
		swapVals(a, left, pivot);
		
	//Double checks that left <= pivot <= right
	assert(a[0] <= a[right]);
	assert(a[pivot] <= a[right]);
	
	//If the array only has 3 elements, then return
	if (right - left <= 2) 
		return pivot;

	//Otherwise, it puts the pivot element at the end and changes pivot
	//to pivot-1, since the pivot point has moved out of the way
	swapVals(a, pivot, (right - 1));
	pivot = right - 1;
	
	do {
		//Make sure that a at ind2 is <= a at ind1, then swaps them
		if (a[ind1] >= a[pivot] && a[ind2] <= a[pivot]) {
			assert(a[ind2] <= a[ind1]);
			swapVals(a,ind1,ind2);
		}

		if (a[ind1] <= a[pivot])
			ind1++;
		if (a[ind2] >= a[pivot])
			ind2--;
	} while (ind1 <= ind2);
	
	swapVals(a,ind1,pivot);
	
	int temp2 = pivot;
	pivot = ind1;
	ind1 = temp2;
	
	//Makes sure that pivot is in the right spot
	assert(a[pivot] >= a[pivot-1] && a[pivot] <= a[pivot+1]);
	
	return pivot;
}



void printArray(int a[], int n) {
	for(int i=0; i<n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}


void quicksort (int a[], int len) {
	qsort(a, 0, len-1);
	return;
}


