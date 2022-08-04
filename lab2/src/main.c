#include <stdlib.h>
#include <stdio.h>
#include "Deykstra.h"


int main (void) {
	char string[12] = {0};
	int N = 0;
	
	if (scanf("%11[^\n]s", string) != 1) {
      printf("bad input");
	    exit(0);
	}
	
	// if str len more than 10 (count of digit from '0' to '9') - no matter to run algorithm
	if (strlen(string) > 10) {
	    printf("bad input");
	    exit(0);
	}
	
	if (scanf("%d", &N) != 1) {
	    printf("bad input");
	    exit(0);
	}
	
	DeykstraPerm(string, N);

	return EXIT_SUCCESS;
}

