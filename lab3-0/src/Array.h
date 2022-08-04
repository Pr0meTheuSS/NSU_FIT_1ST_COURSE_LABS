#pragma once
#include <stdlib.h>
#include <stdio.h>


struct TArray{
	int* Array;
	size_t Size;
};

typedef struct TArray TArray;

void InitArray(TArray* arr, size_t size);
void ReadArrayIntFromConsole(TArray arr);
void PrintArrayIntToConsole(TArray arr);
void ClearArray(TArray* arr);

