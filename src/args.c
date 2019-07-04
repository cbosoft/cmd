#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <cvec.h>

#include "cmd.h"

#define STREQ(A,B) (strcmp(A,B) == 0)
#define STREQ2(A,B,C) (STREQ(A,B) || STREQ(A,C))
#define CHECKNEXT if ((i+1 >= argc) || (argv[i+1][0] == '-')) argerr("argument %s expects a value", argv[i]);

void usage()
{
  fprintf(stderr,
      "\n"
      "  cmd: "BOLD"Molecular Dynamics simulation in c"RESET"\n"
      "\n"
      "  Usage:\n"
      "    cmd -l <load path> -t <time steps> -d <delta time> [-s <save path>]\n"
      "    cmd -n <number particles> [-b <box x> [<box y> <box z>]] -t <time steps> -d <delta time> [-s <save path>]\n"
      "    cmd -h | --help"
      "\n"
    );
}

void argerr(const char *fmt, ...)
{
  size_t mesglen = 256;
  char *mesg = calloc(mesglen, sizeof(char));

  va_list ap;

  va_start(ap, fmt);
  vsnprintf(mesg, mesglen, fmt, ap);
  va_end(ap);

  fprintf(stderr, "  "BG_RED"USAGE ERROR!"RESET": %s\n", mesg);
  usage();
  exit(1);
}




Args *alloc_args()
{
  Args *args = calloc(1, sizeof(Args));
  args->number_particles = 0;
  args->flags = 0;
  args->box = cvec_ones(NDIM);

  return args;
}




Args *parse_args(int argc, const char **argv)
{
  Args *args = alloc_args();

  if (argc == 1) {
    usage();
    exit(1);
  }

  // required params
  int n_set = 0, dt_set = 0, t_set = 0;
  
  for (unsigned int i = 1 ; i < argc; i++) {

    if (STREQ2(argv[i], "-n", "--number-particles")) {

      CHECKNEXT;

      if (FLAGSET(args->flags, ARGS_LOAD))
        argerr("can't both create and load config (-b and -n are incompatible with -l)");

      args->flags |= ARGS_CREATE;

      i++;
      args->number_particles = (cvec_uint)atoi(argv[i]);
      n_set = 1;

      if (args->number_particles == 0)
        argerr("number of particles cannot be zero.");
    }
    else if (STREQ2(argv[i], "-b", "--box")) {

      CHECKNEXT;

      if (FLAGSET(args->flags, ARGS_LOAD))
        argerr("can't both create and load config (-b and -n are incompatible with -l)");

      args->flags |= ARGS_CREATE;

      i++;
      args->box[0] = (cvec_float)atof(argv[i]);

      if (argv[i+1][0] != '-')
        for (int j = 1; j < 3;i++,j++)
          args->box[j] = (cvec_float)atof(argv[i]);
      else
        for (int j = 1; j < 3; j++)
          args->box[j] = args->box[0];

    }
    else if (STREQ2(argv[i], "-l", "--load")) {

      CHECKNEXT;

      if (FLAGSET(args->flags, ARGS_CREATE))
        argerr("can't both create and load config (-b and -n are incompatible with -l)");

      args->flags |= ARGS_LOAD;

      i++;

      args->load_path = argv[i];

    }
    else if (STREQ2(argv[i], "-s", "--save")) {

      CHECKNEXT;

      args->flags |= ARGS_SAVE;

      i++;

      args->save_path = argv[i];

    }
    else if (STREQ2(argv[i], "-t", "--time-steps")) {

      CHECKNEXT;

      i++;

      args->number_steps = (cvec_uint)atoi(argv[i]);
      t_set = 1;

    }
    else if (STREQ2(argv[i], "-d", "--delta-time")) {

      CHECKNEXT;

      i++;

      args->delta_time = (cvec_uint)atof(argv[i]);
      dt_set = 1;

    }
    else if (STREQ2(argv[i], "-h", "--help")) {

      usage();
      exit(0);

    }

  }
  
  if (!n_set)
    argerr("number of particles \"-n\" is a required parameter.");
  if (!dt_set)
    argerr("delta time \"-d\" is a required parameter.");
  if (!t_set)
    argerr("number of steps \"-t\" is a required parameter.");


  return args;
}
