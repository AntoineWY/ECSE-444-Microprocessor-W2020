#ifndef _MA_FILTER_H
#define _MA_FILTER_H

extern void ma_Filter_asm(float* data, float *f_data, int length, int depth);
void ma_Filter_c(float* data, float *f_data, int length, int depth);

#endif
