//Selection sort:
void selection_sort(int A[], int n) {
	for (int i = 0; i < N-1; i++) {
		int min = A[i];
		/* find min */
		int min_i = i;
	for (int j=i+1; j < N; j++) {
		if (A[j] < min) {
			min = A[j];
			min_i = j;
		}
	}
	int temp = A[min_i];
	/* swap */
	A[min_i] = A[i];
	A[i] = temp;
	}
}

//Insertion sort:
void isort(int A[], int n) {
	for (int i = n-2; i >= 0; i--) {
		int temp = A[i];
		for (int j=i+1; j < n; j++) {
			if (A[j] < temp) {
				A[j-1] = A[j];
			} else {
			break;
			}
		}
	A[j-1] = temp;
	}
}




//Quicksort:
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





//Merge sort:
//Linked list

struct node {
	int first;
	struct node *rest;
};

/*
	Purpose: Consumes two references to the first node in linked lists lst1 and lst2,
			 and returns a reference to the first node in the linked list
			 that contains all of the items from lst1 and lst2 in increasing
			 sorted order
	Pre: 	-All elements of lst1 and lst2 must be greater than 0
			-lst1 and lst2's elements must be in increasing order
			-No element may be found more than once in either list
				ie All elements are unique
	Post: 	 Produces a reference to the first node in the linked list
			 that contains all of the items from lst1 and lst2 in 
			 increasing sorted order
*/
struct node *merge(struct node *lst1, struct node *lst2) {
	
	// First checks if either of the lists are NULL
	// If either are NULL, then it returns the other list
	// since no other work is required
	if (lst1 == NULL) {
		return lst2;
	} else if (lst2 == NULL) {
		return lst1;
	}

	// Creates nodes that will allow you to work through the lists
	// without completely changing them
	// cur_lst is the end of the current list being worked on
	// lst*_tmp are the positions of lst* being worked on 
	struct node *lst1_tmp = lst1;
	struct node *lst2_tmp = lst2;
	struct node *cur_lst;
	
	// If the first element of lst1 is the lowest element, then
	// cur_lst is set to lst1, and it starts working using
	// that as the first element. Then sets lst*_tmp to the rest
	// of the respective list
	if (lst1->first < lst2->first) {
		cur_lst = lst1;
		lst1_tmp = cur_lst->rest;
	} else {
		cur_lst = lst2;
		lst2_tmp = cur_lst->rest;
	}

	// Until either the end of lst1 or lst2 has been reached, it
	// checks if both lst1 and lst2 are not NULL, then points cur_lst
	// to the correct next spot in either lst*_tmp 	
	while (lst1_tmp != NULL && lst2_tmp != NULL){
		if (lst1_tmp->first < lst2_tmp->first){
			cur_lst->rest = lst1_tmp;
			lst1_tmp = lst1_tmp->rest;
		} else {
			cur_lst->rest = lst2_tmp;
			lst2_tmp = lst2_tmp->rest;
		}
		cur_lst = cur_lst->rest; 
	}
	
	// Now either lst1_tmp or lst2_tmp are NULL
	// It checks which one, and points the rest of cur_lst
	// to the one that is not NULL
	if (lst1_tmp != NULL){
		cur_lst->rest = lst1_tmp;
	} else {
		cur_lst->rest = lst2_tmp;
	}	
	
	// Lastly it checks which list contains the smallest element,
	// and finally returns that list
	if (lst1->first < lst2->first){
		return lst1;
	} else {
		return lst2;
	}
}




