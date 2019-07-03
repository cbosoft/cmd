#include <stdio.h>

#include "cmd.h"

int main (int argc, const char **argv)
{

  Sim *sim = alloc_sim();

  populate(sim, 1000);

  fprintf(stderr, "it is done.\n");

  free_sim(sim);

  return 0;
}
