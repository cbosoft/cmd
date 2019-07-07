CC 		= gcc
CFLAGS 	= -O0 -g
LINK	= -lcvec -lfftw3 -lm -fopenmp

HDR		= src/cmd.h src/cJSON.h

OBJ 	= \
	obj/args.o \
	obj/cJSON.o \
	obj/error.o \
	obj/fcc.o \
	obj/force.o \
	obj/geometry.o \
	obj/io.o \
	obj/particle.o \
	obj/sim.o

default: cmd

obj/%.o: src/%.c $(HDR)
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ -fPIC $<

cmd: obj/main.o $(OBJ) $(HDR)
	$(CC) $(CFLAGS) -o $@ -fPIC $(OBJ) $(LINK)

geomtest: obj/geomtest.o $(OBJ) $(HDR)
	$(CC) $(CFLAGS) -o $@ -fPIC $(OBJ) $(LINK)
