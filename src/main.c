#include <stdio.h>

#include "cmd.h"


int main (int argc, const char **argv)
{
  Args *args = parse_args(argc, argv);
  
  Sim *sim;
  if (FLAGSET(args->flags, ARGS_CREATE)) {
    sim = alloc_sim();
    populate(sim, args->number_particles);
  }
  else {
    sim = load(args->load_path);
  }
  
  // TODO: run sim

  if (FLAGSET(args->flags, ARGS_SAVE)) {
    save(sim, args->save_path);
  }

  free_sim(sim);

  return 0;
}
