#!/bin/bash
# make
# ./main.out 0 5 "./data/d-10-06.txt"
# make clean

echo "data,solver,voh,nodes,backtrack,runtime" > summary.csv
for data_file in ./data/*; do
    # SB
    for voh in {1..5}; do
        make clean
        make
        output=$(timeout 20m ./main.out 0 $(($voh)) "$data_file")
        if [[ $? -eq 124 ]]; then
            output='-1,-1,-1'
        fi
        echo ""$data_file",BT,$voh,$output" >> summary.csv
    done
    # FC
    for voh in {1..5}; do
        make clean
        make
        output=$(timeout 20m ./main.out 1 $(($voh)) "$data_file")
        if [[ $? -eq 124 ]]; then
            output='-1,-1,-1'
        fi
        echo ""$data_file",FC,$voh,$output" >> summary.csv
    done
done
make clean