#!/bin/bash

# List of original files
files=("mrigidBodySolver.C" "mrigidBodySolver.H" "rigidBodySolverI.H" "rigidBodySolverNew.C")
# Step 2: Replace class name inside the renamed files
for f in mrigidBodySolver*; do
    sed -i 's/\brigidBodySolver\b/mrigidBodySolver/g' "$f"
    echo "Replaced class name in $f"
done
