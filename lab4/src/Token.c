#include "Token.h"


char GetPriority(TToken token) {
  // Pre condition
  assert(token.Type == OPERATOR);

  if (IsOpenBracket(token) || IsCloseBracket(token)) {
    return 0;
  }
  if (token.Value.Operator == '*' || token.Value.Operator == '/') {
    return 1;
  }
  if (token.Value.Operator == '-' || token.Value.Operator == '+') {
    return 2;
  }
  return -1;
}


EBool IsBinary(TToken token) {
  // Pre condition
  assert(token.Type == OPERATOR);

  char binaryOperatorsTable[] = {'*', '+', '-', '/'};
  for (size_t i = 0; i < sizeof(binaryOperatorsTable); i++) {
    if (token.Value.Operator == binaryOperatorsTable[i]) {
      return True;
    }
  }
  return False;
}


EBool IsOpenBracket(TToken token) {
  // Pre condition
  assert(token.Type == OPERATOR);

  if (token.Value.Operator == '(') {
    return True;
  }
  return False;
}


EBool IsCloseBracket(TToken token) {
  // Pre condition
  assert(token.Type == OPERATOR);

  if (token.Value.Operator == ')') {
    return True;
  }

  return False;
}


TToken Calc(TToken leftOperand, TToken rightOperand, TToken operator, ETokenStatus * status) {
  TToken res = {{0}, NUMBER};
  // Pre condition
  if (leftOperand.Type != NUMBER || rightOperand.Type != NUMBER || operator.Type != OPERATOR) {
    *status = SyntaxError;
    return res;
  }
  *status = Success;
  
  if (operator.Value.Operator == '*') {
    res.Value.Operand = leftOperand.Value.Operand * rightOperand.Value.Operand;
  } else if (operator.Value.Operator == '-') {
    res.Value.Operand = leftOperand.Value.Operand - rightOperand.Value.Operand;
  } else if (operator.Value.Operator == '+') {
    res.Value.Operand = leftOperand.Value.Operand + rightOperand.Value.Operand;
  } else if (operator.Value.Operator == '/') {
    if (rightOperand.Value.Operand == 0) {
      *status = DivisionByZero;
    } else {
      res.Value.Operand = leftOperand.Value.Operand / rightOperand.Value.Operand;
    }
  } else {
    *status = SyntaxError;
  }
  return res;
}

