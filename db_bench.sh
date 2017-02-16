#!/bin/bash
totalsize=$(expr 1024 \* 1024 \* 1024 \* 100)
#totalsize=$(expr 1024 \* 1024 \* 100)
benchmarks=fillrandom,stats,readrandom,stats,readrandom,stats
value_size=128
let num=totalsize/value_size
bloom_bits=10
log_open=1
db=/home/ceph/DBStore
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

time out-shared/db_bench --db="$db" --benchmarks="$benchmarks" --value_size="$value_size" --num="$num" --bloom_bits="$bloom_bits" --log_open="$log_open" --max_file_size=4194304 --open_files=1000 --reads=100000 > bench_result_"$value_size"B_"$num"_l"$log_open" 
