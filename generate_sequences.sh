#!/bin/bash
# Define the alphabet
PROTEINS=('A' 'C' 'G' 'T')
#
LENGTH=${#PROTEINS[@]}
# Set the wanted length
N=$1
# Seed the prng
SEED=$$
RANDOM=$$
# Define output file
FILE=input/random-n$1-seed$SEED.fasta
# Insert comment in file
echo "> Random Sequence. Seed $SEED. Length: $1" > ${FILE}
for i in $(seq 1 ${N});
do
    # Get a random index within the PROTEINS array
    idx=$(($RANDOM % ${LENGTH}));
    # Write the corresponding protein to file
    echo -n ${PROTEINS[${idx}]} >> ${FILE}

    # Format the file with new lines and spaces
    if [ $(($i % 50)) == 0 ]; then
        echo "" >> ${FILE}
    elif [ $(($i % 10)) == 0 ]; then
        echo -n " " >> ${FILE}
    fi
done;