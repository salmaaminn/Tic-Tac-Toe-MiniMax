so: xo.o
	gcc xo.o -o so

xo.o: xo.c
	gcc -c xo.c -o xo.o

clean:
	rm xo.o so



