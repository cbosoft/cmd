#include "math.h"

#include "cmd.h"

cvec_float calculate_force(Sim *s, Particle *p1, Particle *p2)
{
  // lennard jone s12-6

  cvec_float dr = get_distance(s, p1, p2);

  if (dr > 2.5)
    return 0.0;

  cvec_float drinv = 1.0/dr;
  cvec_float dr2inv = drinv*drinv;
  cvec_float dr6inv = dr2inv*dr2inv*dr2inv;
  return drinv*(12.0*dr6inv*dr6inv - 6.0*dr6inv);
}
