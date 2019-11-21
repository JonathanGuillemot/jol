all : stats testarray
	echo "compilation terminee"
stats : stats.o intarray.o tools.o
	gcc stats.o intarray.o tools.o -o stats

testarray : testarray.o intarray.o tools.o
	gcc testarray.o intarray.o tools.o -o testarray

intarray.o : intarray.c intarray.h tools.h
	gcc -c intarray.c

testarray.o : testarray.c intarray.h
	gcc -c testarray.c

tools.o : tools.c tools.h
	gcc -c tools.c

stat.o : stats.c intarray.h tools.h
	gcc -c stat.c
