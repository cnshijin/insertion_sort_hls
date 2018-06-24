[TOC]

# 说明
本文所描述的代码源于开源书籍 [Parallel Programming for FPGAs](http://kastner.ucsd.edu/hlsbook/)，其中代码 **insertion_sort_b2b_cell** 是根据书籍的一个扩展作业，由自己独立设计完成，可以连续输入数据流并进行排序，全流水线，中间不需停歇。

## insertion_sort
插入排序算法原型，由于 `while` 条件要同时读取数组 `A`，则无法满足 `#pragma HLS pipeline II=1` 的优化需求。

## insertion_sort_refactored
针对 **insertion_sort** 重构，读取数组 `A` 移出 `while` 条件语句，满足 `#pragma HLS pipeline II=1` 的优化需求。

## insertion_sort_parallel
因为 `while` 循环次数可变化，无法使用优化指令 `UNROLL`，修改代码使用固定循环次数。

## insertion_sort_cell
提取出插入算法的基础原语，然后根据并行数的需求组合。

## insertion_sort_b2b_cell
可以连续输入数据流并排序输出，满足 `II=1`。