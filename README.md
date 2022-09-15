# C+ compiler

1. Building C+ compiler

```
make clean
make all
```

2. Running test cases

CHESS:

I. Creating unoptimized abstract machine code

```
./demo test/chess.c+ -o test/chess_unoptimized
```

This will create chess\_unoptimized.i file.

Creating binary from chess\_unoptimized.i

```
./path/to/assembler/demo test/chess_unoptimized.i
```

This will create binary file test/chess\_unoptimized


II. For performing optimization, we have a commandline flag 'O1'. To create an
optimized abstract machine code, enable the optimization flag. For example,

```
./demo test/chess.c+ -O1 -o test/chess_optimized
```


Following similar steps, executables for test/nqueens.c+ and test/mergeSort.c+ can be created.

3. Enabling debug info

We can also print IR and other debug informations by updating a boolen value
in STEClasses.C:17.

We need to change "debugOn" boolean variable to "true" and follow step 1 and 2
to print debug information.


