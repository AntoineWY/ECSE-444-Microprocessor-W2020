#include <ma_Filter.h>
#include <stdio.h>

float average(float *sample, int length){

    float sum =0;
   
    for(int i = 0; i<length; i++){
        sum = sample[i] + sum;
    }
    float average = sum / length;
    return average;
}



int is_odd_depth(int depth){
    if(depth%2==1){
        return 1;
    }
    else
    {
        return 0;
    }
    
}


void ma_Filter_c(float* data, float *f_data, int length, int depth){

    int i = 0;
	
	
    for (i = 0; i<length; i++){
        
        float average_arr[depth];
				int arr_i = 0; // index for truncated array

				
        if(is_odd_depth(depth) == 1){
				
            for (int j = i-depth/2; j<= i+depth/2 ; j++){
                

                if( (          j < 0 || j>(length -1)        )){
                    average_arr[arr_i] = 0.00;
                }else{
                    average_arr[arr_i] = data[j];
                }
                arr_i++;

            } // until now: got a truncated array float specified to calculate average at f_data[i]
            
        }else{// depth now is a even number
            for (int j = i-depth/2; j<= (i+depth/2 -1) ; j++){
               

                if( (          j < 0 || j  > (length -1)        )){
                    average_arr[arr_i] = 0.00;
                }else{
                    average_arr[arr_i] = data[j];
                }
                arr_i++;

            } 

        }					
        float avg = average(average_arr, depth);
        f_data[i] = avg;
    }
       

   

}



