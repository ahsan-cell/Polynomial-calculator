# Polynomial Operations in C++

This C++ program allows you to perform various operations on polynomials, including addition, subtraction, multiplication, solving for a variable, checking equality, and more. Here's a brief overview of the program and its functions.

## Program Overview

This program provides a menu-based interface to work with polynomials. It supports working with one or two polynomials and offers the following operations:

- Enter a single polynomial or two polynomials.
- Print the entered polynomial(s).
- Solve a polynomial for a specific variable.
- Add two polynomials.
- Subtract the second polynomial from the first.
- Subtract the first polynomial from the second.
- Multiply two polynomials.
- Check if two polynomials are equal.

The program performs these operations efficiently and provides clean output. It uses an array-based representation to store and manipulate polynomial terms.

## Functions

The program consists of several functions, each serving a specific purpose:

- `Input(int &terms, int deg[], int coef[])`: Allows the user to input a polynomial's terms, degrees, and coefficients, and then sorts and removes duplicate degrees.
- `FileInput(int &terms, int deg[], int coef[])`: Reads a polynomial from a file ("polynomial.txt").
- `Solve(int terms, int deg[], int coef[], int variable)`: Solves a polynomial for a given variable.
- `Add(int aterms, int adeg[], int acoef[], int bterms, int bdeg[], int bcoef[], int rterms, int rdeg[], int rcoef[])`: Adds two polynomials.
- `Subtract(int aterms, int adeg[], int acoef[], int bterms, int bdeg[], int bcoef[], int rterms, int rdeg[], int rcoef[])`: Subtracts the second polynomial from the first.
- `Equal(int aterms, int adeg[], int acoef[], int bterms, int bdeg[], int bcoef[])`: Checks if two polynomials are equal.
- `Print(int terms, int deg[], int coef[])`: Prints a polynomial in a user-friendly format.
- `Menu(int aterms, int adeg[], int acoef[], int bterms, int bdeg[], int bcoef[], int rterms, int rdeg[], int rcoef[])`: The main menu to interact with the program, allowing users to choose operations.

## Usage

1. Compile and run the program.
2. Follow the menu prompts to perform various polynomial operations.

Please note that the program reads and writes polynomials to a file named "polynomial.txt" for input and output. You can edit this file manually or choose to enter polynomials via the command line.

This program is a versatile tool for working with polynomials and can be easily extended to handle more complex polynomial operations.

Enjoy working with polynomials using this C++ program!
