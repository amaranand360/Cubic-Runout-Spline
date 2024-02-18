# Cubic Runout Spline Interpolation

This repository contains a C implementation of the Cubic Runout Spline interpolation algorithm. The algorithm interpolates values between given data points with the most extreme endpoint behavior.

## How to Use
- Clone the repository.
- Compile the code using a C compiler.
- Run the executable to input data points and perform spline interpolation.

## Compilation and Execution

Follow these steps to compile and run the program:

### Step 1: Compile Cubic Spline Code

```bash
gcc -c cubic_runout_spline.c -o spline.o
```
### Step 2: Compile Test Code

```bash
gcc -c test_code.c -o test_code.o
```
### Step 3: Link Object Files and Create Executable

```bash
gcc test_code.o spline.o -o test
```
### Step 4: Run the Executable
```
./test
```

## Repository Structure
- `design_document.md`: Overview of the algorithm and design choices.
- `test_code.c`: Test cases for validating the algorithm.
- `cubic_runout_spline.c`: Main code implementing the Cubic Runout Spline algorithm.

## Author
Amar Kumar
