#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#define TEXT_BUFF_LEN 256
#define TEMPL_BUFF_LEN 20


void CompareStrProtocol(unsigned char* text, unsigned char* template, size_t absShift) {
  size_t templateLen = strlen((char*)template);
  for (size_t i = 0; i < templateLen; i++) {
    printf("%zd ", absShift + i);
    if (text[i + absShift] != template[i]) {
      break;
    }
  }
}


size_t CalcHash(unsigned char str[], size_t len) {
  size_t exp = 1;
  size_t hash = 0;
  for (size_t i = 0; i < len; i++) {
    hash += (str[i] % 3) * exp;
    exp *= 3;
  }
  return hash;
}


size_t ReCalcHash(unsigned char* str, size_t len, size_t oldHash) {
  return (oldHash - (str[0] % 3)) / 3 + (str[len] % 3) * pow(3, len - 1);
}


void RabinCarpProtocol(FILE* f, unsigned char templ[]) {
  if (!f) {
    return;
  }
  size_t templateLen = strlen((char*)templ);
  size_t templHash = CalcHash(templ, templateLen);
  printf("%zd ", templHash);

  unsigned char text[TEXT_BUFF_LEN] = {0};
  size_t textLen = fread(text, sizeof(text[0]), TEXT_BUFF_LEN - 1, f);
  if (!textLen) {
    return;
  }

  size_t textHash = CalcHash(text, templateLen);
  size_t absShift = 0;
  do {
    for (size_t i = 0; i <= textLen - templateLen; i++) {
      if (templHash == textHash) {
        CompareStrProtocol(text, templ, i + absShift);
      }
      textHash = ReCalcHash(&text[i], templateLen, textHash);
    }
    if (textLen > templateLen) {
      unsigned char tmpBuffer[256] = {0};
      memcpy(tmpBuffer, &text[textLen - templateLen], (templateLen - 1) * sizeof(text[0]));
      memcpy(text, tmpBuffer, (templateLen - 1) * sizeof(text[0]));
    }
    absShift += textLen;
    textLen = fread(&text[templateLen - 1], sizeof(text[0]), TEXT_BUFF_LEN - templateLen, f);
  }while (textLen != 0);
}


int main(void) {
  unsigned char template[TEMPL_BUFF_LEN] = {0};
  if (scanf("%19[^\n]s", template) != 1) {
    printf("bad input");
    exit(0);
  }
  RabinCarpProtocol(stdin, template);
  return 0;
}

