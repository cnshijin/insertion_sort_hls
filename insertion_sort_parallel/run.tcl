open_project insertion_sort_parallel
set_top insertion_sort_parallel
add_files insertion_sort_parallel.cpp
add_files -tb insertion_sort_parallel_tb.cpp
open_solution "solution1"
set_part {xc7z020clg484-1}
create_clock -period 10 -name default
set_clock_uncertainty 0.5
csim_design -clean
csynth_design
exit
