// Copyright 2022 Y.Olimpiev
#pragma once
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

typedef struct TNumber {
  unsigned long long IntPart;
  double FractPart;
} TNumber;

void ReverseString(char* str);

int CharToInt(char ch);

char IntToChar(int val);

void InitNumber(struct TNumber * numb, char * numb_str, int base);

void ConvertNumberBase(struct TNumber numb, int to_base, char *res);
