#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv) {
	if (argc < 5) return 1;
	
	int min_size = atoi(argv[1]);
	int max_size = atoi(argv[2]);
	int min_cores = atoi(argv[3]);
	int max_cores = atoi(argv[4]);
	
	for(int i = min_size; i <= max_size; i++) {
		for(int j = min_cores; j <= max_cores; j++) {
			cout << i << " " << j << endl;
		}
	}
}
