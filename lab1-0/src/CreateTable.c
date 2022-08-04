//#include "CreateTable.h"
#include <string.h>

void CreateTable(unsigned int table[256], int sub_string[17]){
    
    size_t str_len = 0;
    while(sub_string[str_len] != '\0'){
        str_len++;
    }

    for (size_t i = 0; i < 255; i++){

        table[i] = str_len;
    }

    int lastSymb = sub_string[str_len - 1];
    table[lastSymb] = str_len;

    for (size_t i = 1; i < str_len; i++){

	    unsigned char currSymb = sub_string[str_len - 1 - i];
        
        if (table[currSymb] > i){

            table[currSymb] = i;
	    }
    }
}
