#include "insertion_sort.h"

void insertion_sort(DTYPE A[SIZE]) {
 L1:
  for(int i=1; i<SIZE; i++) {
    DTYPE item = A[i];
    int j = i;
    DTYPE temp = A[j-1];
  L2:
    while(j>0 && temp>item) {
      #pragma HLS pipeline II=1
      A[j] = temp;
      j--;
      temp = A[j-1];
    }

    A[j] = item;
  }
}
