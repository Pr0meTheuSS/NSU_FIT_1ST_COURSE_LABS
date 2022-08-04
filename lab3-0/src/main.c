#include <stdlib.h>
#include <stdio.h>
#include "HeapSort.h"
#include "Array.h" 

int main(void){

	size_t N = 0;
	if(scanf("%zu", &N) != 1){
		printf("\n[STATUS]:\t Error of amount args in func scanf... [LOCATION]:\t in module main\n");
		exit(0);
	}
    
	TArray array = {NULL, 0};
	InitArray(&array, N);
		
	ReadArrayIntFromConsole(array);
	HeapSort(array);
  PrintArrayIntToConsole(array);
		
	ClearArray(&array);
	
	return EXIT_SUCCESS;
}

