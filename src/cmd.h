#pragma once
#include <cvec.h>

// macros {{{


#define NDIM 3

#if NDIM == 3
#define EXPAND(V) V[0], V[1], V[2]
#else
#define EXPAND(V) V[0], V[1]
#endif

#define FG_BLACK   "\033[30m"
#define FG_RED     "\033[31m"
#define FG_GREEN   "\033[32m"
#define FG_YELLOW  "\033[33m"
#define FG_BLUE    "\033[34m"
#define FG_MAGENTA "\033[35m"
#define FG_CYAN    "\033[36m"
#define FG_WHITE   "\033[37m"

#define BG_BLACK   "\033[40m"
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"
#define BG_WHITE   "\033[47m"

#define RESET "\033[0m"
#define BOLD "\033[1m"

// }}}
// types, enums {{{

typedef struct Particle {
  cvec_uint id;
  cvec_float *position;
  cvec_float *force;
  cvec_float diameter;
  cvec_float mass;
} Particle;

typedef struct Sim {
  Particle **particles;
  cvec_uint number_particles;
  cvec_float *box;
  cvec_float *solvent_viscosity;
} Sim;

// }}}
// particle.c {{{

Particle *alloc_particle();
void free_particle(Particle *p);

// }}}
// sim.c {{{

Sim *alloc_sim();
void free_sim(Sim *s);
void add_particle(Sim *s, Particle *p);

// }}}
// error.c {{{

void ferr(const char* src, const char* fmt, ...);
void warn(const char* src, const char* fmt, ...);

// }}}
// fcc.c {{{

void populate(Sim *s, cvec_uint n);

// }}}
// io.c {{{

void save(Sim *s, const char *path);
Sim* load(const char *path);

// }}}
// vim: ft=c foldmethod=marker
