#include "Number.h"


void ReverseString(char* str)
{
    for (size_t i = 0; i < strlen(str) / 2; i++) {
      char tmp = str[i];
      str[i] = str[strlen(str) - 1 - i];
      str[strlen(str) - 1 - i] = tmp;
    }
    str[strlen(str)] = '\0';
}


int ch_to_i(char ch)
{
  int ret = 0;
  switch(toupper(ch) ){
    case '0': {ret = 0; break;}
    case '1': {ret = 1; break;}
    case '2': {ret = 2; break;}
    case '3': {ret = 3; break;}
    case '4': {ret = 4; break;}
    case '5': {ret = 5; break;}
    case '6': {ret = 6; break;}
    case '7': {ret = 7; break;}
    case '8': {ret = 8; break;}
    case '9': {ret = 9; break;}
    case 'A': {ret = 10; break;}
    case 'B': {ret = 11; break;}
    case 'C': {ret = 12; break;}
    case 'D': {ret = 13; break;}
    case 'E': {ret = 14; break;}
    case 'F': {ret = 15; break;}
    default: {ret = -1; break;}
  }
  return ret;
}

char IntToChar(int val)
{
  char ret = 0;
  switch(val ){
    case 0: {ret = '0'; break;}
    case 1: {ret = '1'; break;}
    case 2: {ret = '2'; break;}
    case 3: {ret = '3'; break;}
    case 4: {ret = '4'; break;}
    case 5: {ret = '5'; break;}
    case 6: {ret = '6'; break;}
    case 7: {ret = '7'; break;}
    case 8: {ret = '8'; break;}
    case 9: {ret = '9'; break;}
    case 10: {ret = 'A'; break;}
    case 11: {ret = 'B'; break;}
    case 12: {ret = 'C'; break;}
    case 13: {ret = 'D'; break;}
    case 14: {ret = 'E'; break;}
    case 15: {ret = 'F'; break;}
    default: {ret = EOF; break;}
  }
  return ret;
}

void InitNumber(TNumber* numb, char* numb_str, int base) {
    size_t currSymbolIndex = 0;
    numb->_intPart = 0;
    numb->_fractPart = 0.0;

    while (numb_str[currSymbolIndex] != '.' && numb_str[currSymbolIndex] != '\0') {
      numb->_intPart *= base;
      numb->_intPart += CharToInt(numb_str[currSymbolIndex]);
      currSymbolIndex++;
    }
    currSymbolIndex = 0;
    if (numb_str[currSymbolIndex] == '.') {
      currSymbolIndex++;
      double exp = 1.0 / (double)base;
      while (numb_str[currSymbolIndex] != '\0') {
        numb->_fractPart += CharToInt(numb_str[currSymbolIndex]) * exp;
        exp /= base;
        currSymbolIndex++;
      }
    }
}

void convert_number_base(TNumber numb, int to_base, char* res)
{
    if (numb._intPart == 0) {
      res[0] = '0';
    }

    while (numb._intPart > 0) {
      res[strlen(res)] = i_to_ch(numb._intPart % to_base);
      numb._intPart /= to_base;
    }
    ReverseString(res);

    if (numb._fractPart > 0.0) {
      res[strlen(res)] = '.';
    }

    int FractPartLen = 0;
    while (numb._fractPart > 0.0 && FractPartLen++ <= 12) {
      numb._fractPart *= to_base;
      res[strlen(res)] = i_to_ch((int)floor(numb._fractPart));
      numb._fractPart -= floor(numb._fractPart);
    }
}
