#include <stdio.h>
#include <arm_math.h>
#include <stdev.h>


void stdev_c(float* a1, int length,float* answer){
	
		int i;
	  float mean;
		float sum;
		float variance;
	
		for(i=0; i<length; i++){
				sum = sum + a1[i];
		}
		
		mean = (float)sum/length;
		
		for(i=0; i<length; i++){
				
				variance = variance + (a1[i]-mean)*(a1[i]-mean);
		
		}
		
		variance = (float) variance/(length-1);
		
		*answer = sqrtf(variance);
		
}