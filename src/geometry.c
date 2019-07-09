#include <stdlib.h>
#include <math.h>

#include <cvec.h>

#include "cmd.h"

cvec_float square(cvec_float v) { return (cvec_float)pow(v, 2.0); }

cvec_float mag(cvec_float v) { return (v < 0.0)?(v*-1.0):(v); } 

cvec_float get_distance2(Sim *s, Particle *p1, Particle *p2)
{
  cvec_float *dir_dr = cvec_apply2(p1->position, p2->position, NDIM, &cvec_subtract);
  cvec_float *dr = cvec_apply(dir_dr, NDIM, &mag);
  free(dir_dr);

  for (cvec_uint i = 0; i < NDIM; i++) {
    cvec_float hbox = s->box[i]*0.5;
    if (dr[i] > hbox)
      dr[i] -= s->box[i];
  }

  cvec_float *dr2 = cvec_apply(dr, NDIM, &square);
  cvec_float dist2 = cvec_sum(dr2, NDIM);
  free(dr);
  free(dr2);

  return dist2;
}

cvec_float get_distance(Sim *s, Particle *p1, Particle *p2)
{
  return (cvec_float)pow(get_distance2(s, p1, p2), 0.5);
}
