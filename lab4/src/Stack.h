#pragma once
#include "Token.h"
#include <string.h>


typedef struct TStack {
  struct TStackElement {
    TToken Token;
    struct TStackElement* Next;
  }* Head;
} TStack;


typedef enum EStackStatus {
  NotAvailableStack,
  SuccessStack,
  EmptyStack
} EStackStatus;


typedef struct TStackElement TStackElement;

EStackStatus PopStack(TStack* stack, TToken* token);

EStackStatus PushStack(TStack* stack, TToken token);

EBool IsStackEmpty(TStack* stack);

EStackStatus FreeStack(TStack* stack);

