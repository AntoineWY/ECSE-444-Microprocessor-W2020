#include <stdio.h>



void arrayProduct(float* a1, float* a2, int length,float* retArr){
		
		int i;
		for (i =0; i<length;i++){
				retArr[i] = a1[i] * a2[i];
		}
		

}

