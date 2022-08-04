#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef enum ETokenStatus {
  Success,
  SyntaxError,
  DivisionByZero
} ETokenStatus;


typedef enum EBool {
  False = 0,
  True = 1
} EBool;


typedef enum TokenType {
  NUMBER,
  OPERATOR
} TokenType;


// struct describes iterpreter's tokens
typedef struct TToken {
  union Value {
    // let's agree that the operator is represented by one symbol
    char Operator;
    int Operand;
  } Value;
  TokenType Type;
} TToken;

char GetPriority(TToken token);

EBool IsBinary(TToken token);

EBool IsOpenBracket(TToken token);

EBool IsCloseBracket(TToken token);

TToken Calc(TToken leftOperand, TToken rightOperand, TToken operator, ETokenStatus* status);

