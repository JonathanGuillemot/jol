testarray : testarray.o intarray.o
	gcc testarray.o intarray.o -o testarray
intarray.o : intarray.c intarray.h
	gcc -c intarray.c
testarray.o : testarray.c intarray.h
	gcc -c testarray.c
