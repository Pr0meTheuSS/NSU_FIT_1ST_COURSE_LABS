#include "ReversedPolishNotation.h"


EBool IsOperator(char token) {
  char tokenTable[] = {'+', '-', '*', '/', '(', ')'};
  for (size_t i = 0; i < sizeof(tokenTable); i++) {
    if (token == tokenTable[i]) {
      return True;
    }
  }
  return False;
}


EBool IsValidToken(char token) {
  if (!isdigit(token) && !IsOperator(token)) {
    return False;
  }
  return True;
}


ETokenStatus CheckBrackets(char* str) {
  size_t strLen = strlen(str);
  for (size_t i = 0; i < strLen - 1; i++) {
    if (str[i] == '(' && str[i + 1] == ')') {
      return SyntaxError;
    }
  }
  return Success;
}


ETokenStatus GetRPNStack(char* str, TStack* RPNStack) {
  ETokenStatus status = CheckBrackets(str);
  if (status != Success) {
    FreeStack(RPNStack);
    return status;
  }
  size_t strLen = strlen(str);
  TStack tmpStack = {NULL};
  TToken token = {{0}, OPERATOR};

  for (size_t i = 0; i < strLen; i++) {
    if (!IsValidToken(str[i])) {
      FreeStack(RPNStack);
      FreeStack(&tmpStack);
      return SyntaxError;
    }
    // while curr token's type == number
    if (isdigit(str[i])) {
      token.Type = NUMBER;
      // Accumulate value into token's member Value
      token.Value.Operand *= 10;
      token.Value.Operand += str[i] - '0';
      continue;
    }
    // Push number into res stack
    if (token.Type == NUMBER) {
      PushStack(RPNStack, token);
      // Free buff token
      token.Value.Operand = 0;
    }

    token.Type = OPERATOR;
    token.Value.Operator = str[i];

    if (IsOpenBracket(token)) {
      PushStack(&tmpStack, token);
    }

    if (IsCloseBracket(token)) {
      do {
        if (IsStackEmpty(&tmpStack)) {
          FreeStack(RPNStack);
          FreeStack(&tmpStack);
          return SyntaxError;
        }
        PopStack(&tmpStack, &token);
        if (!IsOpenBracket(token)) {
          PushStack(RPNStack, token);
        }
      }while (!IsOpenBracket(token));
      continue;
    }

    if (IsBinary(token)) {
      TToken currTmpStackHead = {{0}, OPERATOR};

      while (!IsStackEmpty(&tmpStack)) {
        PopStack(&tmpStack, &currTmpStackHead);
          if (IsBinary(currTmpStackHead) && GetPriority(token) >= GetPriority(currTmpStackHead)) {
            PushStack(RPNStack, currTmpStackHead);
          } else {
            // Return poped element back to tmpStack
            PushStack(&tmpStack, currTmpStackHead);
            break;
          }
      }
      PushStack(&tmpStack, token);
    }
    token.Value.Operand = 0;
  }
  // Push number into res stack
  if (token.Type == NUMBER) {
    PushStack(RPNStack, token);
    // Free buff token
    token.Value.Operand = 0;
  }

  while (!IsStackEmpty(&tmpStack)) {
    PopStack(&tmpStack, &token);
    if (token.Type != OPERATOR) {
      FreeStack(RPNStack);
      FreeStack(&tmpStack);
      return SyntaxError;
    }
    PushStack(RPNStack, token);
  }
  // PostCondition
  if (!IsStackEmpty(&tmpStack)) {
    FreeStack(RPNStack);
    FreeStack(&tmpStack);
    return SyntaxError;
  }

  // Reverse Stack
  // with Queue could do not reverse (and with char* str too)
  TStack forReverse = {NULL};

  while (!IsStackEmpty(RPNStack)) {
    PopStack(RPNStack, &token);
    PushStack(&tmpStack, token);
  }
  while (!IsStackEmpty(&tmpStack)) {
    PopStack(&tmpStack, &token);
    PushStack(&forReverse, token);
  }
  while (!IsStackEmpty(&forReverse)) {
    PopStack(&forReverse, &token);
    PushStack(RPNStack, token);
  }
  return Success;
}


ETokenStatus RPNCalc(char* inputString, int* result) {
  TToken token = { {0}, NUMBER};

  TStack resultStack = {NULL};
  TStack tmpStack = {NULL};

  ETokenStatus code = 0;
  if ((code = GetRPNStack(inputString, &resultStack)) != Success) {
    return code;
  }

  while (!IsStackEmpty(&resultStack)) {
    PopStack(&resultStack, &token);
    if (IsStackEmpty(&resultStack) && IsStackEmpty(&tmpStack)) {
      if (token.Type != NUMBER) {
         code = SyntaxError;
      }
      *result = token.Value.Operand;
      break;
    }
    if (token.Type == NUMBER) {
      PushStack(&tmpStack, token);
    }
    if (token.Type == OPERATOR) {
      TToken Operands[2] ={ { {0}, NUMBER}, { {0}, NUMBER} };
      for (size_t i = 0; i < 2; i++) {
        if (!IsStackEmpty(&tmpStack)) {
          PopStack(&tmpStack, &Operands[i]);
        } else {
          FreeStack(&tmpStack);
          FreeStack(&resultStack);
          return SyntaxError;
        }
      }
      PushStack(&resultStack, Calc(Operands[1], Operands[0], token, &code));
      if (code != Success) {
        break;
      }
    }
  }
  FreeStack(&tmpStack);
  FreeStack(&resultStack);
  return code;
}

