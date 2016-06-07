#!/bin/bash

RUN_PATH="/home/pedroeusebio/local/hpctoolkit/bin"


for N in 5000 8000 10000 20000 50000 80000 1000000 200000 500000 800000 1000000 2000000 5000000 8000000 10000000 20000000 50000000 80000000 
do
    mkdir stream-$N
    cd stream-$N
	  gcc -g -o -dstream_array_size=$N ../../memoria/stream.c -o stream$N
    cd ../
done

for N in 5000 8000 10000 20000 50000 80000 1000000 200000 500000 800000 1000000 2000000 5000000 8000000 10000000 20000000 50000000 80000000 
do
    cd stream-$N
    $RUN_PATH/hpcrun -e PAPI_L2_TCM -e PAPI_L1_TCM -e CPUTIME ./stream$N
    cd ../
done

for N in 5000 8000 10000 20000 50000 80000 1000000 200000 500000 800000 1000000 2000000 5000000 8000000 10000000 20000000 50000000 80000000 
do
    cd stream-$N
    $RUN_PATH/hpcstruct ./stream$N
    $RUN_PATH/hpcprof -S stream$N.hpcstruct -I~ hpctoolkit-stream$N-measurements
    cd ../
done

