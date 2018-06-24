#include "insertion_sort_cell.h"

template<typename T, int N>
void cell(hls::stream<T> &in, hls::stream<T> &out) {
#pragma HLS PIPELINE
  static T local = 0;
  T in_copy = in.read();

  if(in_copy>local) {
    out.write(local);
    local = in_copy;
  } else {
    out.write(in_copy);
  }
}

void insertion_sort_cell(hls::stream<DTYPE> &in, hls::stream<DTYPE> &out) {
#pragma HLS INTERFACE axis register depth=32 port=in
#pragma HLS INTERFACE axis register depth=32 port=out
#pragma HLS DATAFLOW
  hls::stream<DTYPE> temp[SIZE-1];

  cell<DTYPE, 0 >(in      , temp[0]);
  cell<DTYPE, 1 >(temp[0] , temp[1]);
  cell<DTYPE, 2 >(temp[1] , temp[2]);
  cell<DTYPE, 3 >(temp[2] , temp[3]);
  cell<DTYPE, 4 >(temp[3] , temp[4]);
  cell<DTYPE, 5 >(temp[4] , temp[5]);
  cell<DTYPE, 6 >(temp[5] , temp[6]);
  cell<DTYPE, 7 >(temp[6] , temp[7]);
  cell<DTYPE, 8 >(temp[7] , temp[8]);
  cell<DTYPE, 9 >(temp[8] , temp[9]);
  cell<DTYPE, 10>(temp[9] , temp[10]);
  cell<DTYPE, 11>(temp[10], temp[11]);
  cell<DTYPE, 12>(temp[11], temp[12]);
  cell<DTYPE, 13>(temp[12], temp[13]);
  cell<DTYPE, 14>(temp[13], temp[14]);
  cell<DTYPE, 15>(temp[14], out);
}
