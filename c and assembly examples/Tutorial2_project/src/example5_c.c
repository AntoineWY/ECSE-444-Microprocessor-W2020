#include <example5.h>

void example5_c(int *a, int *b, int length) {
		int i;
	
		for(i=0 ; i<length ; i++)
			b[i] = a[i];
}
