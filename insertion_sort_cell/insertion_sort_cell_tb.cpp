#include "insertion_sort_cell.h"
#include <iostream>
#include <stdlib.h>

const static int DEBUG = 1;
const static int MAX   = 1000;

int main() {
  int fail = 0;
  DTYPE input[SIZE];
  DTYPE output[SIZE];

  hls::stream<DTYPE> in, out;

  // generate random data to sort
  if(DEBUG) std::cout << "Random Input Data\n";
  srand(20);
  for(int i=0; i<SIZE; i++) {
    input[i] = rand() % MAX + 1;
    if(DEBUG) std::cout << input[i] << " ";
  }

  // process the data through the insertion_cell_sort function
  for(int i=0; i<SIZE*2; i++) {
    if(i<SIZE) {
      // feed in the SIZE elements to be sorted
      in.write(input[i]);
      insertion_sort_cell(in, out);
      output[i] = out.read();
    } else {
      // send in dummy data to flush pipeline
      in.write(MAX);
      insertion_sort_cell(in, out);
      output[i-SIZE] = out.read();
    }
  }

  // sort the data using the insertion_sort function
  insertion_sort(input);

  // compare the results of insertion_sort to insertion_sort_cell
  if(DEBUG) std::cout << "\nSorted Output \n";
  for(int i=0; i<SIZE; i++) {
    if(DEBUG) std::cout << output[i] << "\t";
    if(input[i]!=output[i]) {
      fail = 1;
      std::cout << "golden=" << input[i] << "\thw=" << output[i] << "\n";
    }
  }

  if(fail==0)
    std::cout << "PASS\n";
  else
    std::cout << "FAIL\n";

  return fail;
}
