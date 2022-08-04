#include "HeapSort.h"


void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}


void BuildHeap(int* arr, int size, int index){
	int largest = index;   
	int left = 2 * index + 1; 
	int right = 2 * index + 2; 

	if (left < size && arr[left] > arr[largest]){
		largest = left;
	}
	
	if (right < size && arr[right] > arr[largest]){
		largest = right;
	}
	
	if (largest != index){
		swap(&arr[index], &arr[largest]);
		BuildHeap(arr, size, largest);
	}
}


void HeapSort(TArray array){
	HeapSortInt(array.Array, array.Size);
}


void HeapSortInt(int* array, size_t size){
	// Build Heap 
	for (long long i = size / 2 - 1; i >= 0; i--){
		BuildHeap(array, size, i);
	}

	// Sort Array
	for (long long i = size - 1; i >= 0; i--){
		swap(&array[0], &array[i]);
		BuildHeap(array, i, 0);
	}
}

