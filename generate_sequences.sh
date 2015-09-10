#!/bin/bash
# Define
PROTEINS=('A' 'C' 'G' 'T')
N=$1
echo "> Random Sequence. Seed $2. Length: $1" > input/random-n$1-seed$2.fasta
for i in $(seq 1 ${N});
do
    idx=$RANDOM;
    echo -n ${PROTEINS[${idx} % 4]} >> input/random-n$1-seed$2.fasta
done;