#include "insertion_sort_cell.h"
#include <iostream>
#include <stdlib.h>

const static int DEBUG = 1;
const static int MAX   = 1000;

int main() {
  int fail = 0;
  DTYPE input[SIZE*2];
  DTYPE output0[SIZE], output1[SIZE];

  hls::stream<DTYPE> in;
  hls::stream<DTYPE> out;

  // generate random data to sort
  if(DEBUG) std::cout << "Random Input Data\n";
  srand(20);
  for(int i=0; i<SIZE*2+16; i++) {
    if(i>=SIZE*2) {
      // send in dummy data to flush pipeline
      in.write(MAX);
    } else {
      // feed in the SIZE elements to be sorted
      input[i] = rand() % MAX + 1;
      in.write(input[i]);
      if(DEBUG) std::cout << input[i] << " ";
    }
    if(i==SIZE-1) std::cout << "\n";
  }

  insertion_sort_cell(in, out, SIZE*2+16);

  // process the data through the insertion_cell_sort function
  for(int i=0; i<SIZE*2+16; i++) {
    DTYPE rd_data = out.read();

    if(i<SIZE*2) {
      if(i<SIZE) {
        if(i==0) std::cout << "\nRead Output Sequence: \nFirst 16-words are invalid\n";
        std::cout << rd_data << " ";
      } else {
        output0[i-SIZE] = rd_data;
        std::cout << output0[i-SIZE] << " ";
      }
      if(i==SIZE-1 || i==SIZE*2-1) std::cout << "\n";
    } else {
      output1[i-SIZE*2] = rd_data;
      std::cout << output1[i-SIZE*2] << " ";
    }
  }

  // sort the data using the insertion_sort function
  insertion_sort(input);
  insertion_sort(input+SIZE);

  // compare the results of insertion_sort to insertion_sort_cell
  if(DEBUG) std::cout << "\nSorted Output \n";
  for(int i=0; i<SIZE*2; i++) {
    if (i<SIZE) {
      if(DEBUG) {
        if(i==0) std::cout << "\nThe first sorted array: \n";
        std::cout << output0[i] << " ";
      }

      if(input[i]!=output0[i]) {
        fail = 1;
        std::cout << "golden=" << input[i] << "\thw=" << output0[i] << "\n";
      }
    } else {
      if(DEBUG) {
        if(i==SIZE) std::cout << "\nThe second sorted array: \n";
        std::cout << output1[i-SIZE] << " ";
      }

      if(input[i]!=output1[i-SIZE]) {
        fail = 1;
        std::cout << "golden=" << input[i] << "\thw=" << output1[i-SIZE] << "\n";
      }
    }
  }

  std::cout << "\n";

  if(fail==0)
    std::cout << "PASS\n";
  else
    std::cout << "FAIL\n";

  return fail;
}
