#include "Array.h"


void InitArray(TArray* arr, size_t size){
    arr->Size = size;
    arr->Array = (int*)malloc(sizeof(int) * size);
    if (arr->Array == NULL){
        
        printf("\n[STATUS]:\tError of func malloc...\n [LOCATION]:\tmodule main\n");
        exit(-1);		
    }
}


void ReadArrayIntFromConsole(TArray array){
	for (size_t i = 0; i < array.Size; i++){
		if (scanf("%d", &array.Array[i]) != 1){
			printf("\n[STATUS]:\tError\n[MODULE]:\tmain, func scanf()\n[PROBLEM]:wrong number of entered fields\n");
				ClearArray(&array);
				exit(0);
		}	
	}
}


void PrintArrayIntToConsole(TArray array){
	for (size_t i = 0; i < array.Size; i++){
		printf("%d ", array.Array[i]);
	}
}


void ClearArray(TArray* array){
	free(array->Array);
	array->Size = 0;
}

