#include <stdio.h>

#include <example1.h>
#include <example2.h>
#include <example3.h>
#include <example4.h>
#include <example5.h>
#include <example6.h>
#include <example7.h>
#include <example8.h>

int main() {
	
	int i;
	int e5_fail=0;
	int e6_fail=0;
	
	int iarr[10] = {1,2,3,4,5,6,7,8,9,10};
	int iarr_c[10], iarr_asm[10];
	
	float farr[10] = {1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9,10.1};
	float farr_c[10], farr_asm[10];
	
	
	////////////////////////////////////////
	//					Test Example 1						//
	////////////////////////////////////////
	if(example1_c(5,6) != example1_asm(5,6))
		printf("Error in Example 1\n");
	else
		printf("Example 1 successful\n");
	
	////////////////////////////////////////
	//					Test Example 2						//
	////////////////////////////////////////	
	if(example2_c(5.5,6.6) != example2_asm(5.5,6.6))
		printf("Error in Example 2\n");
	else
		printf("Example 2 successful\n");

	////////////////////////////////////////
	//					Test Example 3						//
	////////////////////////////////////////	
	if(example3_c(5,6) != example3_asm(5,6))
		printf("Error in Example 3\n");
	else
		printf("Example 3 successful\n");

	////////////////////////////////////////
	//					Test Example 4						//
	////////////////////////////////////////
	if(example4_c(5.5,6.6) != example4_asm(5.5,6.6))
		printf("Error in Example 4\n");
	else
		printf("Example 4 successful\n");
	
	////////////////////////////////////////
	//					Test Example 5						//
	////////////////////////////////////////
	example5_c(iarr, iarr_c, 10);
	example5_asm(iarr, iarr_asm, 10);
	
	for(i=0 ; i<10 ; i++)
		if(iarr_c[i] != iarr_asm[i])
			e5_fail = 1;
	
	if(e5_fail == 1)
		printf("Error in Example 5\n");
	else
		printf("Example 5 successful\n");
	
	////////////////////////////////////////
	//					Test Example 6						//
	////////////////////////////////////////
	example6_c(farr, farr_c, 10);
	example6_asm(farr, farr_asm, 10);
	
	for(i=0 ; i<10 ; i++)
		if(farr_c[i] != farr_asm[i])
			e6_fail = 1;
	
	if(e6_fail == 1)
		printf("Error in Example 6\n");
	else
		printf("Example 6 successful\n");

	////////////////////////////////////////
	//					Test Example 7						//
	////////////////////////////////////////
	if(example7_c(5) != example7_asm(5))
		printf("Error in Example 7\n");
	else
		printf("Example 7 successful\n");

/*
	////////////////////////////////////////
	//					Test Example 8						//
	////////////////////////////////////////
	if(example8_c(5) != example8_asm(5))
		printf("Error in Example 8\n");
	else
		printf("Example 8 successful\n");
*/ 
	return 0;
}
