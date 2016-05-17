#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

int main() {
	
	cout << "Single PC" << endl;
	// Single PC tests
	for(int alg = 0; alg <= 1; alg++) {
	for(int n_proc = 1; n_proc <= 8; n_proc*=2) {
	for(int size = 25; size <= 32; size++) {
		cout << size << " "
			 << n_proc << " "
			 << 1 << " "
			 << alg << " ";
		cout.flush();
		
		stringstream str;
		str << "mpirun -np " << n_proc << " ./sieve_mpi " 
			<< size << " " 
			<< 0 << " " 
			<< 0 << endl;
		system(str.str().c_str());
	}}}
	
	cout << "Multi PC" << endl;
	// Multi PC tests
	for(int alg = 0; alg <= 1; alg++) {
	for(int n_proc = 1; n_proc <= 4; n_proc*=2) {
	for(int size = 25; size <= 32; size++) {
		cout << size << " "
			 << 8 << " "
			 << 4 << " "
			 << alg << " ";
		cout.flush();
				
		stringstream str;
		str << "mpirun --hostfile hostfile -np " << 8 << " ./sieve_mpi " 
			<< size << " " 
			<< 4 << " " 
			<< alg << endl;				
		system(str.str().c_str());	
		

	}}}
}
