#include "BoyerMooreProtocol.h"

void BoyerMooreProtocol(const char* filename){
 
    FILE * in = fopen(filename, "rb");

    if (in == NULL){
        printf("\nError of reading txt file ..\n");
        exit(0);
    }

    size_t sub_str_len = 0;
    int sub_str[17] = {0};
    int tmp_symb = 0;

    // Read template from file
    while ((tmp_symb = getc(in)) != '\n'){
        sub_str[sub_str_len] = tmp_symb;
        sub_str_len++;
    }

    unsigned int offset_table[256] = {0};
    CreateTable(offset_table, sub_str);

    // All file size - template size - '\n' after template
    fseek(in, 0, SEEK_END);
    size_t text_len = ftell(in) - sub_str_len - 1;
    fseek(in, 0, SEEK_SET);

    size_t i = sub_str_len - 1;
    size_t pos_in_text = i;
    size_t count_match_before = 0;

    while (pos_in_text < text_len){
	
        int curr_symb_in_text = 0;
	    printf("%zu ", 1 + pos_in_text);
        
        fseek(in, pos_in_text + sub_str_len  + 1, SEEK_SET);
        curr_symb_in_text = getc(in);

        if (curr_symb_in_text == sub_str[i]){

            if (i == 0){
                
                i = sub_str_len - 1;
                pos_in_text += offset_table[sub_str[i]] + count_match_before;
                count_match_before = 0;
	        }
            else{
                i--;
                pos_in_text--;
		        count_match_before++;
            }
        }
        else{
            
            if (count_match_before){
                size_t offset = offset_table[sub_str[sub_str_len - 1]] + count_match_before;               
                pos_in_text = pos_in_text + offset;
            }
            else{
                size_t offset = offset_table[curr_symb_in_text];                
                pos_in_text = pos_in_text + offset; 
            }            
            count_match_before = 0;
            i = sub_str_len - 1;
        }
    }

    fclose(in);
}
