#ifndef _STACK_PRIVATE
#define _STACK_PRIVATE

#include <stdio.h>
#include "stackPublic.h"
#include "util.h"

/* structure declarations */
struct stack {
  void **array;
  int index;
  int size;
};

static void stack_print_inverse_r(FILE *fp, stack_t *sp, int i, void (*print)(FILE *, void *));

#endif
