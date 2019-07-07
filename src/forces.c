#include "cmd.h"

cvec_float calculate_force(Sim *s, Particle *p1, Particle *p2)
{
  // temp: TODO
  cvec_float dr2 = get_distance2(s, p1, p2);
  cvec_float dr2inv = 1.0/dr2;
  cvec_float dr6inv = dr2inv*dr2inv*dr2inv;
  
  return dr6inv - dr6inv*dr6inv;
}
