#include <stdio.h>

#include "cmd.h"


int main (int argc, const char **argv)
{
  Sim *sim = alloc_sim();

  Particle *p1 = alloc_particle();
  cvec_set_constant(p1->position, NDIM, 0.0);
  add_particle(sim, p1);

  Particle *p2 = alloc_particle();
  cvec_set_constant(p2->position, NDIM, 1.0);
  add_particle(sim, p2);

  cvec_float dr = get_distance(sim, p1, p2);

  if (dr != 0.0) {
    cvec_test_fail(
        "geometry test", 
        "did not calculate distance between two particles in the same position correctly");
  }
  else {
    cvec_test_pass(
        "geometry test", 
        "calculated distance between two particles in the same position correctly!");
  }

  free_sim(sim);

  return 0;
}
