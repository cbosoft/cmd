#include <stdlib.h>

#include <cvec.h>

#include "cmd.h"




Sim *alloc_sim()
{
  Sim *s = calloc(1, sizeof(Sim));
  
  s->box = cvec_ones(NDIM);
  s->number_particles = 0;

  return s;
}




void free_sim(Sim *s)
{
  free(s->box);
  for (cvec_uint i = 0; i < s->number_particles; i++) {
    free_particle(s->particles[i]);
  }
  free(s);
}




void add_particle(Sim *s, Particle *p)
{
  if (s->number_particles)
    s->particles = realloc(s->particles, (s->number_particles+1) * sizeof(Particle*));
  else
    s->particles = calloc(1, sizeof(Particle*));

  s->particles[s->number_particles] = p;
  s->number_particles ++;
}
