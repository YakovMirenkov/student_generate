CFALGS = -O3
CFLAGS_DEBUG = -g -W -Wall -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -fstack-protector-all -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wno-long-long -Wmissing-declarations

all: generate.out generate_debug.out

generate.out: main.c
	gcc $(CFLAGS) $< -o $@
generate_debug.out: main.c
	gcc $(CFLAGS_DEBUG) $< -o $@

mrproper:
	rm -f *.o *.out
