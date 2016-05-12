
#define BLOCK_LOW(i,n,p) ((i)*(n)/(p))
#define BLOCK_HIGH(i,n,p) (BLOCK_LOW((i)+1,n,p)-1)
#define BLOCK_SIZE(i,n,p) (BLOCK_LOW((i)+1,n,p)-BLOCK_LOW(i,n,p))
#define BLOCK_OWNER(index,n,p) ((((p)*(index)+1)-1)/(n))

#define NUM_TO_STORAGE(n) (((n)-3)>>1)
#define STORAGE_TO_NUM(n) (((n)<<1)+3)

#include <cstdlib>
#include <iostream>
#include <vector>
#include <stdio.h> 
#include "mpi.h" 

using namespace std;

int main(int argc, char** argv) {
	
	// Return if wrong number of arguments:
	if (argc < 2) {
		std::cout << "usage: range [omp_threads]" << std::endl;
		return -1;
	}
	
	// Parse range:
	int range = atoi(argv[1]);
	if (range > 32) range = 32;
	else if (range < 1) range = 1;

	// Define the superior limit:
	size_t N = (1 << range); 
	size_t N_odd = N/2 -1; 

    int rank, size, value; 
    timespec Time1, Time2;
    
    MPI_Init( &argc, &argv ); 
    MPI_Comm_size( MPI_COMM_WORLD, &size ); 
    MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 

	// Init
	std::vector<bool> primes(BLOCK_SIZE(rank,N,size),false);
	
	if (rank == 0) clock_gettime(CLOCK_REALTIME, &Time1);

	int k = 2;
	for (;;) {
		MPI_Bcast(&k,1,MPI_INT,0, MPI_COMM_WORLD);
		if (k*k > N) break;
		
		// Find j
		int j = BLOCK_LOW(rank,N,size);
		if (j % k != 0) j = BLOCK_LOW(rank,N,size) + k - (BLOCK_LOW(rank,N,size) % k);
		if (j < k*k) j = k*k;
		
		// Mark multiples in [k^2, N]:
		for (int i = j; i <= BLOCK_HIGH(rank,N,size); i += k)
			primes[i-BLOCK_LOW(rank,N,size)] = true;

		// Find lowest unmarked number
		if (rank == 0)
			do { k++;} while (primes[k-BLOCK_LOW(rank,N,size)]);
	};
	int sum = 0, sum_r;
	for(int i = ((rank==0) ? 2 : 0); i < BLOCK_SIZE(rank,N,size); i++) {
		if (!primes[i]) {
			//printf("%d ",i+BLOCK_LOW(rank,N,size));
			sum++;
		}
	}
	//printf("\n");
	MPI_Reduce(&sum,&sum_r,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	
	if (rank==0) {
		clock_gettime(CLOCK_REALTIME, &Time2);
		double t1 = Time1.tv_sec + ((double)Time1.tv_nsec)/1e9;
		double t2 = Time2.tv_sec + ((double)Time2.tv_nsec)/1e9;
		
		cout << sum_r << " ";
		cout << (t2-t1)	<< endl;
	} 

    MPI_Finalize(); 
    return 0; 
} 
