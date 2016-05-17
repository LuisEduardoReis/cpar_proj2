CC=g++
CFLAGS=-std=c++11

all:
	$(CC) $(CFLAGS) -O2 Profiler.cpp sieve_cpp.cpp -fopenmp -o sieve
	$(CC) tester.cpp -o tester
	$(CC) tester_mpi.cpp -o tester_mpi
	mpiCC -O2 openmpi_sieve.cpp -o sieve_mpi
clean:
	rm *o sieve tester sieve_mpi
test:
	make all
	./tester 25 32 0 8 | ./sieve
test_mpi:
	make all
	mpirun -np 4 ./sieve_mpi 20
	mpirun --hostfile hostfile -np 16 ./sieve_mpi 20
	mpirun --hostfile hostfile -np 16 ./sieve_mpi 20 0 1
	mpirun --hostfile hostfile -np 16 ./sieve_mpi 20 8 0
	mpirun --hostfile hostfile -np 16 ./sieve_mpi 20 8 1


