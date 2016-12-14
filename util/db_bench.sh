#!/bin/bash
totalsize=$(expr 1024 \* 1024)
benchmarks=fillseq,fillrandom
value_size=$[64]
let num=totalsize/value_size
bloom_bits=10
log_open=1
for i in `seq 1 3`;
do 
    ./db_bench --benchmarks="$benchmarks" --value_size="$value_size" --num="$num" --bloom_bits="$bloom_bits" --log_open="$log_open" > bench_result_"$value_size"B_"$num"
 #   log_open=0
  #  ./db_bench --benchmarks="$benchmarks" --value_size="$value_size" --num="$num" --bloom_bits="$bloom_bits" --log_open="$log_open" 
  #  log_open=1
    let value_size=value_size*16
    let num=totalsize/value_size
done
#