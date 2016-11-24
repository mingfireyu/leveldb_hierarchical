#!/bin/bash
totalsize=$(expr 1024 \* 1024 \* 1024 \* 10)
totalsize=$(expr 1024 \* 1024)
benchmarks=fillseq,fillrandom
value_size=$[64]
value_size=65536
let num=totalsize/value_size
bloom_bits=10
log_open=1
db=/home/ming/testdb
# for i in `seq 1 3`;
# do 
#     time ./db_bench --db="$db" --benchmarks="$benchmarks" --value_size="$value_size" --num="$num" --bloom_bits="$bloom_bits" --log_open="$log_open"  > bench_result_"$value_size"B_"$num"_l"$log_open" 
#     log_open=0
#     time ./db_bench --db="$db" --benchmarks="$benchmarks" --value_size="$value_size" --num="$num" --bloom_bits="$bloom_bits" --log_open="$log_open" > bench_result_"$value_size"B_"$num"_l"$log_open" 
#     log_open=1
#     let value_size=value_size*16
#     let num=totalsize/value_size
# done
#

    time ./db_bench --db="$db" --benchmarks="$benchmarks" --value_size="$value_size" --num="$num" --bloom_bits="$bloom_bits" --log_open="$log_open"  > bench_result_"$value_size"B_"$num"_l"$log_open" 
    log_open=0
    time ./db_bench --db="$db" --benchmarks="$benchmarks" --value_size="$value_size" --num="$num" --bloom_bits="$bloom_bits" --log_open="$log_open" > bench_result_"$value_size"B_"$num"_l"$log_open" 
