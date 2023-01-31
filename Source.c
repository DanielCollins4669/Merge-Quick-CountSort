#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

int arrA[50000];
int size = 5000;
int recMerge, recQuick, compQuick, compMerge, swapQuick, swapMerge = 0;


void merge(int[], int, int, int);
void mergeSort(int[], int, int);


void quickSort(int[], int, int);
void quickSortIt(int[], int, int);

int partition(int[], int, int);
int partition1(int[], int, int);


void countSort(int[], int, int);

void swap(int*, int*);


void main() {
	//uses time to create populate array with random ints 0->999 inclusive
	long lt = time(NULL);
	srand(lt);
	for (int i = 0; i < size; i++) {
		arrA[i] = rand() % 1000;
		//printf("%d\n", arrA[i]);
	}

	int maxVal = 0;
	for (int i = 0; i < size; i++)
	{
		if (arrA[i] > maxVal)
		{
			maxVal = arrA[i];
		}
	}//printf("Max= %d\n", maxVal);
	//clock_t time = clock();
	//double timetaken;
	mergeSort(arrA, 0, size - 1);
	//timetaken = clock() - time;
	printf("MergeSort Recursive Calls = \t%d\nMergeSort Data Comaparisons = \t%d\nMergeSort Swaps =\t%d\n\n", recMerge, compMerge, swapMerge);

	//clock_t time2 = clock();
	quickSort(arrA, 0, size - 1);
	//timetaken = clock() - time2;
	printf("QuickSort Recursive Calls = \t%d\nQuickSort Data Comparisons = \t%d\nQuickSort Swaps =\t%d\n", recQuick, compQuick, swapQuick);

	//clock_t time3 = clock();
	countSort(arrA, size, maxVal);
	//timetaken = clock() - time3;
	//printf("CountSort TimeTaken = %f\n", timetaken / CLOCKS_PER_SEC);

	//for (int i = 0; i < size; i++) {
	//	printf("%d\n", arrA[i] );
	//}
}



//mergeSort to sort values in an integer array arrA[]
// lb = 0 and ub = size - 1 for the first call
void mergeSort(int arrA[], int lb, int ub) {

	recMerge++;
	int mid;
	if (lb < ub) {
		mid = ((lb + ub) / 2);
		mergeSort(arrA, lb, mid);
		mergeSort(arrA, mid + 1, ub);
		merge(arrA, lb, mid, ub);
	}

}


// merge two sorted portions of an integer array arrA[]: 
// portions are lb to mid and mid+1 to ub
void merge(int arrA[], int lb, int mid, int ub) {

	recMerge++;
	int i, j, k;
	int size = ub - lb + 1;
	int* arrC;
	//create arrC[] to be of size needed for current merge
	arrC = (int*)malloc(size * sizeof(int));

	i = lb;
	j = mid + 1;
	k = 0;

	while (i <= mid && j <= ub) {
		compMerge++;
		if (arrA[i] <= arrA[j]) {
			swapMerge++;
			arrC[k] = arrA[i];
			i++;
		}
		else {
			swapMerge++;
			arrC[k] = arrA[j];
			j++;
		}
		k++;
	} //end while

	// write out anything left in i part
	while (i <= mid) {
		swapMerge++;
		arrC[k] = arrA[i];
		i++;
		k++;
	}
	// write out anything left in j part
	while (j <= ub) {
		swapMerge++;
		arrC[k] = arrA[j];
		j++;
		k++;
	}

	//write back from arrC to arrA so correct values are in place for next merge
	i = lb;
	k = 0;
	while (i <= ub) {
		arrA[i] = arrC[k];
		i++;
		k++;
	}
}


void quickSort(int arrA[], int startval, int endval) {
	recQuick++;
	if ((endval - startval) < 1) {
		return;
	}
	else {
		int k = partition2(arrA, startval, endval);
		//now sort the two sub-arrays
		quickSort(arrA, startval, k - 1);  //left partition
		quickSort(arrA, k + 1, endval);   //right partition
	}
}
// better version of partition .. no nested loop
// pivot at startval as before
int partition2(int arrA[], int startval, int endval)
{
	int k;
	int pivot = arrA[startval];
	int i = startval;

	for (k = startval + 1; k <= endval; k++) { // k keeps incrementing to the end
		compQuick++;
		if (arrA[k] <= pivot) {
			i++;   // i only increments when there is a new value to add to the <= portion
			if (i != k) {

				swap(&arrA[i], &arrA[k]);
			}
		}
	}
	swap(&arrA[i], &arrA[startval]);  // put pivot in correct location i
	return(i);
}

void swap(int* a, int* b)
{
	swapQuick++;
	int temp = *a;
	*a = *b;
	*b = temp;
}

void countSort(int arrA[], int size, int maxVal)
{

	int i, value, count;
	int* freq, * arrB;
	int freqSize;

	freqSize = maxVal + 1;

	freq = (int*)malloc(freqSize * sizeof(int));   //create freq[]
	arrB = (int*)malloc(size * sizeof(int));       //create arrB[] same size as arrA[]

	// initialise freq[]
	for (i = 0; i < freqSize; i++) {
		freq[i] = 0;
	}

	// count
	for (i = 0; i < size; i++) {
		++freq[arrA[i]];
	}

	// get <= in freq[]
	for (i = 1; i < freqSize; i++) {
		freq[i] = freq[i] + freq[i - 1];
	}

	// place values from arrA into arrB; update freq[]
	for (i = 0; i < size; i++) {
		value = arrA[i];			//value to sort
		count = freq[value];		//<= freq of value
		arrB[count - 1] = value; 	//place value in arrB
		--freq[value];				//decrement freq[]
	} //next value in arrA

	//write back sorted values to arrA[] now that sorting finished
	for (i = 0; i < size; i++) {
		arrA[i] = arrB[i];
	}
}
