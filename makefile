all : stats debug morpion
	echo "compilation terminee"

stats : stats.o intarray.o tools.o
	gcc stats.o intarray.o tools.o -o stats

debug : debug.o intarray.o tools.o jstr.o stringarray.o charray2D.o file.o
	gcc debug.o intarray.o tools.o jstr.o stringarray.o charray2D.o file.o -o debug -lm

morpion : morpion.o tools.o charray2D.o file.o jstr.o intarray.o
	gcc morpion.o tools.o charray2D.o file.o jstr.o intarray.o -o morpion

intarray.o : intarray.c intarray.h tools.h
	gcc -c -O3 intarray.c

jstr.o : jstr.c jstr.h tools.h intarray.h
	gcc -c -O3 jstr.c

debug.o : debug.c intarray.h jstr.h stringarray.h charray2D.h file.h
	gcc -c -O3 debug.c

stringarray.o : stringarray.c stringarray.h tools.h jstr.h
	gcc -c -O3 stringarray.c


tools.o : tools.c tools.h 
	gcc -c -O3 tools.c

stats.o : stats.c intarray.h tools.h
	gcc -c -O3 stats.c

charray2D.o : charray2D.c charray2D.h tools.h file.h
	gcc -c -O3 charray2D.c

file.o : file.c file.h tools.h jstr.h
	gcc -c -O3 file.c

morpion.o : morpion.c morpion.h tools.h charray2D.h
	gcc -c -O3 morpion.c
