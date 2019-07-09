#include <stdlib.h>
#include <math.h>

#include "cmd.h"




cvec_float calculate_pe(Sim *s, Particle *p1, Particle *p2)
{
  // lennard jone s12-6

  cvec_float dr = get_distance(s, p1, p2);

  if (dr > 2.5)
    return 0.0;

  cvec_float drinv = 1.0/dr;
  cvec_float dr2inv = drinv*drinv;
  cvec_float dr6inv = dr2inv*dr2inv*dr2inv;
  return (12.0*dr6inv*dr6inv - 6.0*dr6inv);
}



void set_forces(Sim *s)
{
  Particle *pi, *pj;
  for (cvec_uint i = 0; i < s->number_particles; i++, pi = s->particles[i]) {
    for (cvec_uint j = 0; j < s->number_particles; j++, pj = s->particles[j]) {
      cvec_float pe = calculate_pe(s, pi, pj);
      cvec_float *dr = get_sep_vec(s, pi, pj);
      cvec_float get_fvec(cvec_float v) { return pe/v; }
      cvec_float *force_vec = cvec_apply(dr, NDIM, get_fvec);

      for (cvec_uint k = 0; k < NDIM; k++) {
        pi->force[k] += force_vec[k];
        pj->force[k] -= force_vec[k];
      }

      free(force_vec);
      free(dr);

    }
  }
}
