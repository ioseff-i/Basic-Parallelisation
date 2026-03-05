#!/bin/bash

# neuron_omp_run.sh
# Shell script to compile and run OpenMP neuron code on macOS (M1/M2/M3)

# 1. Check if LLVM is installed via Homebrew
if ! brew list llvm &>/dev/null; then
    echo "Homebrew LLVM not found. Installing..."
    brew install llvm
else
    echo "Homebrew LLVM found."
fi

# 2. Set LLVM path
LLVM_PATH=$(brew --prefix llvm)
echo "Using LLVM at: $LLVM_PATH"

# 3. Compile neuron_omp.c with OpenMP
echo "Compiling neuron_omp.c..."
$LLVM_PATH/bin/clang -fopenmp \
    -I$LLVM_PATH/include \
    -L$LLVM_PATH/lib \
    neuron_omp.c -o neuron_omp -lm

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi
echo "Compilation successful."

# 4. Set number of threads and run
export OMP_NUM_THREADS=8
echo "Running neuron_omp with $OMP_NUM_THREADS threads..."
./neuron_omp