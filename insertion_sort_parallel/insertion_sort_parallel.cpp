#include "insertion_sort_parallel.h"
#include "assert.h"

#ifndef __SYNTHESIS__
#include <iostream>
#endif

void insertion_sort_parallel(DTYPE A[SIZE], DTYPE B[SIZE]) {
#pragma HLS ARRAY_PARTITION variable=B complete dim=1
 L1:
  for(int i=0; i<SIZE; i++) {
#pragma HLS PIPELINE II=1
    DTYPE item = A[i];
  L2:
    for(int j=SIZE-1; j>=0; j--) {
      DTYPE temp;
      if(j>i) { // 忽略 B[] 的原始数据
        temp = B[j];
      } else if(j>0 && B[j-1]>item) { // cond(j>i) 确保 B[j-1] 来自于 A[]
        temp = B[j-1];
      } else {
        temp = item;
        if(j>0) item = B[j-1];
      }
      B[j] = temp;
    }
#ifndef __SYNTHESIS__
    for(int i=0; i<SIZE; i++)
      std::cout << B[i] << " ";

    std::cout << "\n";
#endif
  }
}
