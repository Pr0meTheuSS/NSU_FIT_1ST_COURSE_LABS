#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "CreateTable.h"
#define ALPHABET_SIZE 256
#define TEMPLATE_MAX_LEN 17

void BoyerMooreProtocol(FILE* in);
void CreateTable(unsigned int offset_table[ALPHABET_SIZE], int template[TEMPLATE_LEN]);
