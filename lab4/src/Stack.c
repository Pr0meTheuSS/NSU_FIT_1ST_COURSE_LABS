#include "Stack.h"


TStackElement* InitStackElement(TToken token) {
  TStackElement* ret = malloc(sizeof(TStackElement));
  assert(ret);
  memcpy(&ret->Token, &token, sizeof(TToken));
  ret->Next = NULL;
  return ret;
}


EStackStatus PopStack(TStack* stack, TToken* token) {
  // Pre Conditions
  if (!stack) {
    return NotAvailableStack;
  }
  if (!stack->Head) {
  return EmptyStack;
  }

  memcpy(token, &stack->Head->Token, sizeof(TToken));
  TStackElement* ForDelete = stack->Head;
  stack->Head = stack->Head->Next;
  free(ForDelete);

  return SuccessStack;
}

EStackStatus PushStack(TStack* stack, TToken token) {
  // Pre Conditions
  if (!stack) {
    return NotAvailableStack;
  }

  TStackElement* newHead = InitStackElement(token);
  newHead->Next = stack->Head;
  stack->Head = newHead;
  return SuccessStack;
}


EBool IsStackEmpty(TStack* stack) {
  // Pre Conditions
  assert(stack);

  if (!stack->Head) {
    return True;
  }

  return False;
}


EStackStatus FreeStack(TStack* stack) {
  if (!stack) {
    return NotAvailableStack;
  }

  TToken ForDelete = { {0}, OPERATOR};
  while (!IsStackEmpty(stack)) {
    PopStack(stack, &ForDelete);  
  }
  return SuccessStack;
}

