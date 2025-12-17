#!/bin/bash
foamCleanTutorials
blockMesh
snappyHexMesh -overwrite
cp -r 0.orig 0
rm -r 0/alpha.water
cp -r 0/alpha.water.org alpha.water
rm -r processor*
setFields
decomposePar
