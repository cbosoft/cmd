#include <stdlib.h>

#include <cvec.h>

#include "cmd.h"




Sim *alloc_sim()
{
  Sim *s = calloc(1, sizeof(Sim));
  
  s->box = cvec_zeros(NDIM);

  return s;
}




void free_sim(Sim *s)
{
  free(s->box);
  free(s);
}
