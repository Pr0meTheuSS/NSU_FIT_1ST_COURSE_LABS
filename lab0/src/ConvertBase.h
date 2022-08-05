// Copyright 2022 Y.Olimpiev
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Number.h"

#ifndef true
  #define true 1
#endif

#ifndef false
  #define false 0
#endif

void BadInput();

int IsValidNumberFormat(char* numb_str, int base);

void ConvertFromBaseToBase(char* numb_str,
                           int fromBase,
                           int toBase,
                           char Res[128]);

