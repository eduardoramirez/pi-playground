#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <string.h>
#include <pthread.h>

#include <sys/timeb.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "governor_part1.h"

// Workload that traverses allocated memory area in a reverse order (to minimize prefetching effect)
static int DEF_ITERATION = 10000;
static int DEF_STRIDE = 1024;
static int DEF_SIZE = 256*1024;

static int* v;
void workload_init(int STRIDE, int SIZE) {
	// Set up array
	v = (int*)malloc(sizeof(int)*SIZE);
	int i;
	for (i = STRIDE; i < SIZE; i += STRIDE) {
		v[i] = (int)&v[i-STRIDE];
	}
	v[0] = (int)&v[i-STRIDE];

	// Warmup the memory
	int* p = v;
	do {
		p = (int*)*p;
	} while (p != (int*)v);
}

void workload_finish() {
	free(v);
}

void workload_body(int iteration, int STRIDE, int SIZE) {
	if (SIZE <= STRIDE) return;

	// Get result
	long long sum_t = 0;
	int n = 0;
	int* p = v;
	int i;

	for (i = 0; i < iteration; i++) {
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 
		p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; p = (int*)*p; 

	}

}

static long long get_current_time_us() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long long curTime = (long long)tv.tv_sec * 1000 * 1000 + (long long)tv.tv_usec;
	return curTime;
}



static inline void reset_counters()
{
	// Reset all cycle counter and event counters
	asm volatile ("mcr p15, 0, %0, c9, c12, 0\n\t" :: "r"(0x00000017));  
}

static inline void get_counters()
{
    unsigned int L1_access, L1_miss, L2_access, L2_miss, cycle_counter; 

    asm volatile("mcr p15, 0, %0, c9, c12, 5\n\t" :: "r"(0x00000000)); // PMSELR select counter 0
    asm volatile("mrc p15, 0, %0, c9, c13, 2\n\t" : "=r" (L1_access)); // PMXEVCNTR read event 0

    asm volatile("mcr p15, 0, %0, c9, c12, 5\n\t" :: "r"(0x00000001)); // PMSELR select counter 1
    asm volatile("mrc p15, 0, %0, c9, c13, 2\n\t" : "=r" (L1_miss)); // PMXEVCNTR read event 0

    asm volatile("mcr p15, 0, %0, c9, c12, 5\n\t" :: "r"(0x00000002)); // PMSELR select counter 2
    asm volatile("mrc p15, 0, %0, c9, c13, 2\n\t" : "=r" (L2_access)); // PMXEVCNTR read event 0

    asm volatile("mcr p15, 0, %0, c9, c12, 5\n\t" :: "r"(0x00000003)); // PMSELR select counter 3
    asm volatile("mrc p15, 0, %0, c9, c13, 2\n\t" : "=r" (L2_miss)); // PMXEVCNTR read event 0

    asm volatile("mrc p15, 0, %0, c9, c13, 0\n\t" : "=r" (cycle_counter)); // PMXEVCNTR read event 0

    printf("L1 Access: %u\n", L1_access);
    printf("L1 Miss: %u\n", L1_miss);
    printf("L2 Access: %u\n", L2_access);
    printf("L2 Miss: %u\n", L2_miss);
    printf("cycle count: %u\n", cycle_counter);
}

int main(int argc, char *argv[]) {
	char szOldGovernor[32];
	unsigned long long t0, t1;

	// Initialize
	set_governor("userspace", szOldGovernor);
	set_by_max_freq(); // You can also test the minimum frequency using "set_by_min_freq()"
    //set_by_max_freq();
	workload_init(DEF_STRIDE, DEF_SIZE);
	printf("Measurement start.\n");
	
	// 1. Reset measurement metrics
	t0 = get_current_time_us();
	reset_counters();

	// 2. Run workload
	workload_body(DEF_ITERATION, DEF_STRIDE, DEF_SIZE);

	// 3. Here, you may need to get performance counters.
    get_counters();
    t1 = get_current_time_us();

	// Print results
	int freq = get_cur_freq();
	printf("Exe_time: %lld us at %d\n", t1-t0, freq);

	// Finish the program
	workload_finish();
	set_governor(szOldGovernor, NULL);

	return 0;
}
