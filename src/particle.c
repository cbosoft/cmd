#include <stdlib.h>

#include <cvec.h>

#include "cmd.h"




Particle *alloc_particle()
{
  Particle *p = calloc(1, sizeof(Particle));

  p->position = cvec_zeros(NDIM);
  p->force = cvec_zeros(NDIM);
  p->diameter = 1.0;
  p->mass = 1.0;

  return p;
}




void free_particle(Particle *p)
{
  free(p->position);
  free(p->force);
  free(p);
}
