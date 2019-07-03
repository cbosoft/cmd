CC 		= gcc
CFLAGS 	= -O0 -g
LINK	= -lcvec -lfftw3 -lm -fopenmp

HDR		= src/cmd.h
OBJ 	= obj/main.o \
				obj/sim.o \
				obj/particle.o \
				obj/error.o \
				obj/fcc.o

default: cmd

obj/%.o: src/%.c $(HDR)
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ -fPIC $<

cmd: $(OBJ) $(HDR)
	$(CC) $(CFLAGS) -o $@ -fPIC $(OBJ) $(LINK)
