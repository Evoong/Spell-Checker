#include <stdio.h>
#include <stdlib.h>
#include "cs136-trace.h"
#include "nst.h"

int main(void) {
  const int CMD_INSERT = lookup_symbol("insert");
  const int CMD_CHECK = lookup_symbol("check");
  const int CMD_MEM = lookup_symbol("memory");
  
  struct nst *spellchecker = nst_create();

  int cmd = INVALID_SYMBOL;
  while ((cmd = read_symbol()) != INVALID_SYMBOL) {
    if (cmd == CMD_INSERT) {
      char input[100] = { '\0' };
      scanf("%s", input);
      nst_insert(spellchecker, input);
    } else if (cmd == CMD_CHECK) {
      char input[100] = { '\0' };
      scanf("%s", input);
      printf("The word >%s< is spelt %s.\n" , input, nst_spellcheck(spellchecker, input) ? "correctly" : "incorrectly");
    } else if (cmd == CMD_MEM) {
      printf("Info: using %d bytes of memory\n", nst_memory(spellchecker));
    } else {
      printf("ERROR: unknown command\n");
    }
  }
  nst_destroy(spellchecker);
  return EXIT_SUCCESS;
}