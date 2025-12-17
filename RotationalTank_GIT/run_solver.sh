of2206
rm -r processor*
decomposePar
mpirun -np 16 olaFlow -parallel|tee log.solver_olaflow
