#include "Deykstra.h"


void Swap(char* a,  char* b) {
  char tmp = *a;
  *a = *b;
  *b = tmp;
}


void DeykstraPerm(char* string, int n) {
	CheckFormat(string);

	for (int j = 0; j < n; j++) {
		int firstDisorderedElementIndex = -1;
		// Try to find disordered pair from end of string
		for (int i = (int)strlen(string) - 2; i >= 0 ; i--) {	
			if (string[i] < string[i + 1]) {
				firstDisorderedElementIndex = i;
				break;
			}
		}

		// If all pairs are in decreasing order - all work done
		if (firstDisorderedElementIndex == -1) {
			printf("\n");
			return;
		}

		int supIndex = firstDisorderedElementIndex + 1;

		for (size_t k = supIndex; k < strlen(string); k++) {
			// On right side from disordered pair search index of element to swap
			if (string[k] > string[firstDisorderedElementIndex] && string[k] <= string[supIndex]) {	
				supIndex = k;
			}
		}   

		Swap(&string[firstDisorderedElementIndex], &string[supIndex]);

		int fromIndexToReverse = firstDisorderedElementIndex + 1;
		// Reverse tail 
		for (size_t k = 0; k < (strlen(string) - fromIndexToReverse) / 2; k++) {
			Swap(&string[fromIndexToReverse + k], &string[strlen(string) - k - 1]);
		}
		printf("%s\n", string);
	}
}


void CheckFormat(char* string) {
	int digitFreqTable[10] = {0};
	
	for (size_t k = 0; k < strlen(string); k++) {
		if (!isdigit(string[k])) {
			printf("bad input");
			exit(0);
		}
		digitFreqTable[string[k] -'0']++;
	}

	for (size_t k = 0; k < strlen(string); k++) {
		if (digitFreqTable[k] > 1) { 
			printf("bad input");
			exit(0);
		}
	}
}

