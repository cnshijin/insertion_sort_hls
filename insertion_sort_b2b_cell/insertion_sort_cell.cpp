#include "insertion_sort_cell.h"

template<typename T, int N>
void cell(hls::stream<T> &in, hls::stream<T> &out, const int size) {
  static T local = 0;
  T temp;
  int k = 0;

  for(int i=0; i<size; i++) {
#pragma HLS PIPELINE II=1
    T in_copy = in.read();

    if(in_copy>local || k<=N) {
      temp = local;
      local = in_copy;
    } else {
      temp = in_copy;
    }
    out.write(temp);

    k++;
    if(k==SIZE) k=0;
  }
}

void insertion_sort_cell(hls::stream<DTYPE> &in, hls::stream<DTYPE> &out, const int size) {
#pragma HLS DATAFLOW
#pragma HLS INTERFACE axis port=out
#pragma HLS INTERFACE axis port=in
#pragma HLS STREAM variable=in  depth=48 dim=1
#pragma HLS STREAM variable=out depth=48 dim=1
#pragma HLS INTERFACE ap_none port=size

  hls::stream<DTYPE> temp[17];
#pragma HLS STREAM variable=temp depth=2 dim=1

 L0:
  for(int i=0; i<size; i++) {
#pragma HLS PIPELINE II=1
    DTYPE var;
    var = in.read();
    temp[0].write(var);
  }

  cell<DTYPE, 0 >(temp[0] , temp[1] , size);
  cell<DTYPE, 1 >(temp[1] , temp[2] , size);
  cell<DTYPE, 2 >(temp[2] , temp[3] , size);
  cell<DTYPE, 3 >(temp[3] , temp[4] , size);
  cell<DTYPE, 4 >(temp[4] , temp[5] , size);
  cell<DTYPE, 5 >(temp[5] , temp[6] , size);
  cell<DTYPE, 6 >(temp[6] , temp[7] , size);
  cell<DTYPE, 7 >(temp[7] , temp[8] , size);
  cell<DTYPE, 8 >(temp[8] , temp[9] , size);
  cell<DTYPE, 9 >(temp[9] , temp[10], size);
  cell<DTYPE, 10>(temp[10], temp[11], size);
  cell<DTYPE, 11>(temp[11], temp[12], size);
  cell<DTYPE, 12>(temp[12], temp[13], size);
  cell<DTYPE, 13>(temp[13], temp[14], size);
  cell<DTYPE, 14>(temp[14], temp[15], size);
  cell<DTYPE, 15>(temp[15], temp[16], size);

 L1:
  for(int i=0; i<size; i++) {
#pragma HLS PIPELINE II=1
    DTYPE var;
    var = temp[16].read();
    out.write(var);
  }
}
