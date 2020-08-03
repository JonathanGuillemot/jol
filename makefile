all : stats debug morpion
	echo "compilation terminee"

stats : stats.o intarray.o tools.o
	gcc stats.o intarray.o tools.o -o stats

debug : debug.o intarray.o tools.o jstr.o stringarray.o charray2D.o file.o KVdata.o image.o
	gcc debug.o intarray.o tools.o jstr.o stringarray.o charray2D.o file.o KVdata.o image.o -o debug -lm

morpion : morpion.o tools.o charray2D.o file.o jstr.o intarray.o
	gcc morpion.o tools.o charray2D.o file.o jstr.o intarray.o -o morpion

intarray.o : intarray.c intarray.h tools.h
	gcc -c -O3 -Werror intarray.c

jstr.o : jstr.c jstr.h tools.h intarray.h
	gcc -c -O3 -Werror jstr.c

debug.o : debug.c intarray.h jstr.h stringarray.h charray2D.h file.h image.h
	gcc -c -O3 -Werror debug.c

stringarray.o : stringarray.c stringarray.h tools.h jstr.h
	gcc -c -O3 -Werror stringarray.c


tools.o : tools.c tools.h 
	gcc -c -O3 -Werror tools.c

stats.o : stats.c intarray.h tools.h
	gcc -c -O3 -Werror stats.c

charray2D.o : charray2D.c charray2D.h tools.h file.h
	gcc -c -O3 -Werror charray2D.c

image.o : image.c image.h tools.h file.h
	gcc -c -O3 -Werror image.c

file.o : file.c file.h tools.h jstr.h
	gcc -c -O3 -Werror file.c

morpion.o : morpion.c morpion.h tools.h charray2D.h
	gcc -c -O3 -Werror morpion.c

KVdata.o : KVdata.c KVdata.h tools.h stringarray.h file.h
	gcc -c -O3 -Werror KVdata.c
