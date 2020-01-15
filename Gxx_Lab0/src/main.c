#include <stdio.h>
#include <add.h>
#include <ma_filter.h>

int main(){

		//printf("hello world!");
	
	
	
	
	  /*
		float n1 = 1.1;
		float n2 = 2.2;
	
		float c = add_c(n1,n2);
		float a = add_asm(n1,n2);
	
		printf("c add runs as = %f \n", c);
		printf("asm add runs as = %f\n", a);
	*/
	
	
	
		float data[] = {0.1, 0.2, 0.3, 0.4};
    float *f_data;
    int l =4;
    int d = 3;
    f_data = (float*) malloc(l*sizeof(float));
   
    //ma_Filter_c(data, f_data, l,d);
		ma_Filter_asm(data, f_data, l,d);
		
    for(int i =0; i<l; i++){
        printf("%f \n", f_data[i]);
    }

	
	
	
	
		return 0;
}