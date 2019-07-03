#include "cmd.h"

int main (int argc, const char **argv)
{

  Sim *sim = alloc_sim();

  free_sim(sim);

  return 0;
}
