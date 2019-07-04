CC 		= gcc
CFLAGS 	= -O0 -g
LINK	= -lcvec -lfftw3 -lm -fopenmp

HDR		= src/cmd.h src/cJSON.h

OBJ 	= \
	obj/cJSON.o \
	obj/error.o \
	obj/fcc.o \
	obj/io.o \
	obj/main.o \
	obj/particle.o \
	obj/sim.o

default: cmd

obj/%.o: src/%.c $(HDR)
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ -fPIC $<

cmd: $(OBJ) $(HDR)
	$(CC) $(CFLAGS) -o $@ -fPIC $(OBJ) $(LINK)
