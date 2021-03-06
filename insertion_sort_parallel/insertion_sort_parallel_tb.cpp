#include "insertion_sort_parallel.h"
#include <iostream>
#include <stdio.h>

int main() {
  int fail = 0;
  DTYPE A[SIZE] = {1, 6, 3, 7, 2, 5, 3, 0, 9, 10, 11, 12, 13, 14, 15, 8};
  DTYPE B[SIZE];

  printf("B[] Before sort: ");
  for(int i=0; i<SIZE; i++) {
    std::cout << B[i] << " ";
    B[i] = -2;
  }

  std::cout << "\n";

  insertion_sort_parallel(A, B);

  printf("B[] After sort: ");
  for(int i=0; i<SIZE; i++)
    std::cout << B[i] << " ";

  std::cout << "\n";

  for(int i=1; i<SIZE; i++) {
    if(B[i] < B[i-1]) {
      std::cout << i << " " << B[i-1] << ">" << B[i] << "\n";
      fail = 1;
    }
  }

  if(fail == 1)
    printf("FAILED\n");
  else
    printf("PASS\n");
}
