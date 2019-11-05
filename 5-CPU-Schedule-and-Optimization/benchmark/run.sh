gcc -o benchmark benchmark.c vec.c combine.c src/cpe.c src/lsquare.c src/fcyc.c src/clock.c -DFLOAT
./benchmark
