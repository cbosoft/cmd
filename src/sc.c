#include <stdio.h>
#include <math.h>

#include <cvec.h>

#include "cmd.h"

void populate(Sim *s, cvec_uint n)
{
  if (n == 0)
    ferr("populate", "Number of particles cannot be zero.");

  cvec_uint number_cells = n;
  cvec_float volume = cvec_prod(s->box, NDIM);
  cvec_float volume_cell = volume / ((cvec_float)number_cells);
  cvec_float cell_side = (cvec_float)pow(volume_cell, 1.0/((double)NDIM));

  cvec_uint cells_per_length = (cvec_uint)(ceil(s->box[0] / cell_side));

  cvec_int *cell_pos = cvec_int_zeros(NDIM);
  for (cell_pos[0] = 0; cell_pos[0] < cells_per_length; cell_pos[0]++) {
    for (cell_pos[1] = 0; cell_pos[1] < cells_per_length; cell_pos[1]++) {
#if NDIM == 3
      for (cell_pos[2] = 0; cell_pos[2] < cells_per_length; cell_pos[2]++) {
#endif

        Particle *p = alloc_particle();

        p->position = cvec_zeros(NDIM);
        for (cvec_uint j = 0; j < NDIM; j++)
          p->position[j] = cell_pos[j] * cell_side;

        p->id = s->number_particles;

        add_particle(s, p);

        if (s->number_particles == n)
          goto end;

#if NDIM == 3
      }
#endif
    }
  }
  
end:
  if (s->number_particles < n)
    ferr("populate", "not enough particles were allocated (%u/%d).", s->number_particles, n);
}
