#include <example7.h>

int example7_c(int a) {
	int retval = 0;
	
	while((a>>retval++) != 1);
	return --retval;
}
