# Big picture 
The project implements the Simplex method, a well-known algorithm for solving linear programming problems used in optmization problems. Its objective is to iteratively modify a tableau and select entering and leaving variables to determine the optimal solution of the problem. Additionally, the project effectively deals with artificial variables and constraints using the two-phase method

# Advantages

1-Provides a practical implementation of the Simplex method for linear programming problems.

2-Handles cases with artificial variables and constraints through the two-phase method.

3-Allows users to input coefficients and constraints conveniently.

4-Prints the simplex tableau in a tabular format for better understanding.

5-Detects unbounded and infeasible solutions.

6-Supports finding alternative solutions, if they exist. 

# How does it work

The project works by taking input from the user, including the number of variables, coefficients of the objective function, and constraints. It initializes the necessary data structures, such as vectors and matrices, to represent the tableau. The project then performs iterations of the simplex algorithm, modifying the tableau, selecting entering and leaving variables, and updating the basic and non-basic variables. This process continues until an optimal solution is reached or it determines that the problem is unbounded or infeasible. The project also checks for alternative solutions by examining the coefficients of non-basic variables in the objective function.

https://github.com/aalsayed70/simplex_method/assets/89813459/83f310ee-d735-430b-8f9f-2f8f2db82e49
