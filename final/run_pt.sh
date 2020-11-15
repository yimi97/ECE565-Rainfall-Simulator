#! /bin/bash

echo "Using parallel"
for i in 1 2 4 8
do
    echo "THREAD = $i"
    ./rainfall_pt i 50 0.5 4096 ../../Input/measurement_4096x4096.in
    python ./check.py 4096 measurement_4096x4096.out output.txt
    rm output.txt
    sleep 1
    ./rainfall_pt i 35 0.5 2048 ../../Input/sample_2048x2048.in
    python ./check.py 2048 sample_2048x2048.out output.txt
    rm output.txt
    sleep 1
    ./rainfall_pt i 30 0.75 512 ../../Input/sample_512x512.in
    python ./check.py 512 sample_512x512.out output.txt
    rm output.txt
    sleep 1
    ./rainfall_pt i 30 0.25 128 ../../Input/sample_128x128.in
    python ./check.py 128 sample_128x128.out output.txt
    rm output.txt
    sleep 1
    ./rainfall_pt i 20 0.5 16 ../../Input/sample_16x16.in
    python ./check.py 16 sample_16x16.out output.txt
    rm output.txt
    sleep 1
    ./rainfall_pt i 10 0.25 4 ../../Input/sample_4x4.in
    python ./check.py 4 sample_4x4.out output.txt
    rm output.txt
    sleep 1
done
echo "-------"
