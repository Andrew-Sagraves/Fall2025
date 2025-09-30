#!/bin/bash
# Usage: ./run_glimmer.sh genome.fna output_prefix
# Make sure this script is in the same folder as the Glimmer executables (or adjust the paths below).

if [ $# -lt 2 ]; then
    echo "Usage: $0 <genome.fna> <output_prefix>"
    exit 1
fi

GENOME=$1
PREFIX=$2

# Step 1: Find long ORFs
./long-orfs -n -t 1.15 $GENOME ${PREFIX}.longorfs

# Step 2: Extract training sequences
./extract $GENOME ${PREFIX}.longorfs > ${PREFIX}.train

# Step 3: Build ICM model
./build-icm -r ${PREFIX}.icm < ${PREFIX}.train

# Step 4: Run Glimmer predictions
./glimmer3 $GENOME ${PREFIX}.icm ${PREFIX}

# Step 5: Extract predicted genes into FASTA
./extract $GENOME ${PREFIX}.predict > ${PREFIX}.genes.fna

echo "✅ Glimmer pipeline finished!"
echo "Results:"
echo " - Predictions: ${PREFIX}.predict"
echo " - Coordinates: ${PREFIX}.coord"
echo " - Gene sequences (FASTA): ${PREFIX}.genes.fna"

