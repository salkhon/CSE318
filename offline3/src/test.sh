#!/bin/bash
# dataset name, penalty, constructive heuristic

# make 
# ./main.out car-f-92 0 0
# make clean
echo "data,pen,con-heu,timeslots,penalty-constructive,penalty-kempe,penalty-pairswap" > output.csv
for pen in {0..1}; do
    for con_heu in {0..3}; do
        for data_file in ../data/*.crs; do
            make clean
            make
            filename=$(basename "$data_file" .crs)
            echo $filename
            output=$(./main.out "$filename" $pen $con_heu)
            if [[ $? -eq 124 ]]; then
                output='-1,-1,-1,-1'
            fi
            echo "$output" >> output.csv
        done
    done
done
make clean