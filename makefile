all : stats debug
	echo "compilation terminee"

stats : stats.o intarray.o tools.o
	gcc stats.o intarray.o tools.o -o stats

debug : debug.o intarray.o tools.o jstr.o stringarray.o
	gcc debug.o intarray.o tools.o jstr.o stringarray.o -o debug -lm

intarray.o : intarray.c intarray.h tools.h
	gcc -c intarray.c

jstr.o : jstr.c jstr.h tools.h intarray.h
	gcc -c jstr.c

debug.o : debug.c intarray.h jstr.h stringarray.h
	gcc -c debug.c

stringarray.o : stringarray.c stringarray.h tools.h jstr.h
	gcc -c stringarray.c


tools.o : tools.c tools.h 
	gcc -c tools.c

stats.o : stats.c intarray.h tools.h
	gcc -c stats.c
