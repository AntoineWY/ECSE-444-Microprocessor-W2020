#include <example8.h>

int example8_c(int a) {
	if(a<=1)
		return 1;
	return a*example8_c(a-1);
	
}
