# KnitroCpp

An unofficial C++ interface for the nonlinear programming solver [Artelys Knitro](https://www.artelys.com/fr/solveurs/knitro/).

The philosphy of this interface is to reproduce the C interface in a C++ way, that is
* Replacing the functions by class methods
* Replacing the return codes by exceptions
* Getting rid of the `free` calls
* Defining callbacks through lamabda functions

Examples:
* [hs15](examples/hs15.cpp): a simple example that shows how to input linear structures, quadratic structures, and evaluation callbacks.

Compile examples:
* The `KNITRODIR` environment variable must have been set correctly.
* Then:
```shell
bazel build -- //...
```

Run an example:
```shell
./bazel-bin/examples/hs15
```
```
=======================================
          Commercial License
         Artelys Knitro 13.1.0
=======================================

Knitro presolve eliminated 0 variables and 0 constraints.


Problem Characteristics                                 (   Presolved)
-----------------------
Objective goal:  Minimize
Objective type:  general
Number of variables:                                  2 (           2)
    bounded below only:                               0 (           0)
    bounded above only:                               1 (           1)
    bounded below and above:                          0 (           0)
    fixed:                                            0 (           0)
    free:                                             1 (           1)
Number of constraints:                                2 (           2)
    linear equalities:                                0 (           0)
    quadratic equalities:                             0 (           0)
    gen. nonlinear equalities:                        0 (           0)
    linear one-sided inequalities:                    0 (           0)
    quadratic one-sided inequalities:                 2 (           2)
    gen. nonlinear one-sided inequalities:            0 (           0)
    linear two-sided inequalities:                    0 (           0)
    quadratic two-sided inequalities:                 0 (           0)
    gen. nonlinear two-sided inequalities:            0 (           0)
Number of nonzeros in Jacobian:                       4 (           4)
Number of nonzeros in Hessian:                        3 (           3)

Knitro using the Interior-Point/Barrier Direct algorithm.

  Iter      Objective      FeasError   OptError    ||Step||    CGits 
--------  --------------  ----------  ----------  ----------  -------
       0    9.090000e+02   3.000e+00
      10    3.065000e+02   9.480e-11   9.480e-11   1.358e-05        0

EXIT: Locally optimal solution found.

Final Statistics
----------------
Final objective value               =   3.06499999937285e+02
Final feasibility error (abs / rel) =   9.48e-11 / 3.16e-11
Final optimality error  (abs / rel) =   9.48e-11 / 6.50e-12
# of iterations                     =         10 
# of CG iterations                  =         10 
# of function evaluations           =         18
# of gradient evaluations           =         11
# of Hessian evaluations            =         10
Total program time (secs)           =       0.02235 (     0.005 CPU time)
Time spent in evaluations (secs)    =       0.00001

===============================================================================

Return status: 0
Objective value: 306.5
Absolute feasibility error: 9.47961e-11
Relative feasibility error: 3.15987e-11
Absolute optimality error: 9.47961e-11
Relative optimality error: 6.49799e-12
x0: 0.5
x1: 2
```
