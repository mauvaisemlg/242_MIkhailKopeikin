all: prog third.so

prog: main.c first.c second.c first.h
	gcc -fPIC -shared first.c -o libfirst.so
	gcc main.c second.c -L. -lfirst -Wl,--wrap=fred -Wl,--wrap=john -o prog

third.so: third.c
	gcc -fPIC -shared third.c -o third.so

run:
	LD_LIBRARY_PATH=. ./prog

run_load:
	LD_LIBRARY_PATH=. LD_PRELOAD=./third.so ./prog

clean:
	rm -f prog *.so