#include <stdio.h>

#include "cmd.h"


int main (int argc, const char **argv)
{
  Sim *sim = alloc_sim();

  populate(sim, 10);

  fprintf(stderr, "(%f, %f, %f)  (%f, %f, %f)\n", EXPAND(sim->particles[0]->position), EXPAND(sim->particles[9]->position));

  free_sim(sim);

  return 0;
}
