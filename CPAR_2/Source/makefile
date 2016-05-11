CC=g++
CFLAGS=-std=c++11

all:
	$(CC) $(CFLAGS) Profiler.cpp sieve_cpp.cpp  -o program -m64
	$(CC) tester.cpp -o tester -m64
	$(CC) sieve_original.cpp -o program_original -fopenmp -m64
	mpiCC openmpi_sieve.cpp -o program_openmpi -m64
clean:
	rm *o program
test:
	./tester 1 32 0 8 | ./program_original
