#include "BoyerMooreProtocol.h"

void CreateTable(unsigned int table[ALPHABET_SIZE], int template[TEMPLATE_MAX_LEN]) {
  size_t strLen = strlen(template);
  strnset(table, strLen, 256);
  table[strLen - 1] = strLen;

  for (size_t i = 1; i < strLen; i++) {
    unsigned char currSymb = template[strLen - 1 - i];
      if (table[currSymb] > i) {
        table[currSymb] = i;
    }
  }
}
// TODO: remake by BoyerMoorProtocol(FILE* in, char template[TEMPLATE_MAX_LEN])
void BoyerMooreProtocol(FILE* in){
  size_t templateLen = 0;
  int template[17] = { 0 };

  while ((template[templateLen] = getc(in)) != '\n'){
    templateLen++;
  }

  unsigned int offsetTable[256] = {0};
  CreateTable(offsetTable, template);

  fseek(in, 0, SEEK_END);
  size_t text_len = ftell(in) - templateLen - 1;
  fseek(in, 0, SEEK_SET);

  size_t i = templateLen - 1;
  size_t pos_in_text = i;
  size_t count_match_before = 0;

  while (pos_in_text < text_len) {
    int curr_symb_in_text = 0;
    printf("%zu ", 1 + pos_in_text);
      
    fseek(in, pos_in_text + templateLen  + 1, SEEK_SET);
    curr_symb_in_text = getc(in);

    if (curr_symb_in_text == template[i]){
        if (i == 0){            
            i = templateLen - 1;
            pos_in_text += offsetTable[template[i]] + count_match_before;
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
            size_t offset = offsetTable[template[templateLen - 1]] + count_match_before;               
            pos_in_text = pos_in_text + offset;
        }
        else{
            size_t offset = offsetTable[curr_symb_in_text];                
            pos_in_text = pos_in_text + offset; 
        }            
        count_match_before = 0;
        i = templateLen - 1;
    }
  }
}
