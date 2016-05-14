
#define BLOCK_LOW(i,n,p) ((i)*(n)/(p))
#define BLOCK_HIGH(i,n,p) (BLOCK_LOW((i)+1,n,p)-1)
#define BLOCK_SIZE(i,n,p) (BLOCK_LOW((i)+1,n,p)-BLOCK_LOW(i,n,p))
#define BLOCK_OWNER(index,n,p) ((((p)*(index)+1)-1)/(n))


#include <cstdlib>
#include <iostream>
#include <vector>
#include <stdio.h> 
#include "mpi.h" 

using namespace std;

int main(int argc, char** argv) {
	
	// Return if wrong number of arguments:
	if (argc < 2) {
		std::cout << "usage: range [omp_threads] [separate_search]" << std::endl;
		return -1;
	}
	
	// Parse range:
	int range = atoi(argv[1]);
	if (range > 32) range = 32;
	else if (range < 1) range = 1;

	// Define the superior limit:
	size_t N = (1 << range); 
	size_t N_odd = N/2 -1; 
	
	// Parse n_omp option
	int n_omp = 0;
	if (argc >= 3) {
		n_omp = atoi(argv[2]);
	}
	
	// Parse separate_search option
	bool separate_search = false;
	if (argc >= 4) {
		separate_search = strcmp("1",argv[3]);
	}

    int rank, size, value; 
    timespec Time1, Time2;
    
    MPI_Init( &argc, &argv ); 
    MPI_Comm_size( MPI_COMM_WORLD, &size ); 
    MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 

	if (size*size > N) {
		if (rank == 0) cout << "Too many processes for given arguments!" << endl;
		return -1;
	}

	// Init
	std::vector<bool> primes(BLOCK_SIZE(rank,N,size),false);
	std::vector<bool> seed_primes(BLOCK_SIZE(0,N,size),false);
		
	if (rank == 0) clock_gettime(CLOCK_REALTIME, &Time1);
	int k = 2;
	for (;;) {
		if (!separate_search) MPI_Bcast(&k,1,MPI_INT,0, MPI_COMM_WORLD);
		
		// Stop when k > sqrt(N)
		if (k*k > N) break;		

		// Mark multiples in seed block:
		if (rank != 0 && separate_search)
			#pragma omp parallel for num_threads(n_omp)
			for (size_t i = k*k; i <= BLOCK_HIGH(0,N,size); i += k)
				seed_primes[i] = true;
		
		// Find j
		size_t j = BLOCK_LOW(rank,N,size) + (k - (BLOCK_LOW(rank,N,size) % k)) % k;
		if (j < k*k) j = k*k;
		
		// Mark multiples in block:
		#pragma omp parallel for num_threads(n_omp)
		for (size_t i = j; i <= BLOCK_HIGH(rank,N,size); i += k)
			primes[i-BLOCK_LOW(rank,N,size)] = true;

		// Find lowest unmarked number
		if (rank == 0)
			do { k++;} while (primes[k]);
		else if (separate_search) {
			do { k++;} while (seed_primes[k]);
		}
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
		
		cout << range << " ";
		cout << size  << " ";
		cout << n_omp << " ";
		cout << (separate_search ? 1:0) << " ";		
		cout << sum_r << " ";
		cout << (t2-t1)	<< endl;
	} 

    MPI_Finalize(); 
    return 0; 
} 
