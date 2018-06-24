#ifndef _INSERTION_SORT_CELL_H
#define _INSERTION_SORT_CELL_H
#include "hls_stream.h"
#include "insertion_sort.h"
extern void insertion_sort_cell(hls::stream<DTYPE> &in, hls::stream<DTYPE> &out);
#endif
