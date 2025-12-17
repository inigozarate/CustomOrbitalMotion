#!/bin/bash

# List of type names to replace (e.g., class names)
#types=("mrigidBody" "mmasslessBody" "mjointBody" "msphere" "mcuboid" "mnull" "mjoint" "mfloating" \
       "mRx" "mRy" "mRz" "mRa" "mRs" "mRzyx" "mRxyz" "mRyxz" "mPx" "mPy" "mPz" "mPa" "mPxyz" \
       "mlinearSpring" "mlinearDamper" "mexternalForce"
types=("mrigidBodyInertia","mrigidBodyModelState","mrigidBodyModel","mrestraints","mrestraint")

# Loop over each type name
for item in "${types[@]}"
do
    echo "Replacing $item → m$item"
    grep -rlw "$item" . | xargs sed -i "s/\b$item\b/m$item/g"
done
