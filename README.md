# The Arithmetic Expression Evaluator: A Brief Overview.

This command-line program evaluates arithmetic expressions based on operator precedence rules (PEMDAS). 
It supports basic arithmetic operations, including addition, subtraction, multiplication, division, modulo, and exponentiation. 
It also handles parentheses and provides error messages for invalid input.

## How to use the Arithmetic Expression Evaluator:

### Begin by installation:
    1. Clone or download the repository this can be accomplished by either using the git clone command or downloading the zip.
    2. Navigate to the project directory (not yet existent so doesn't have a name yet)
    3. Compile the program with the respective C++ compiler.

Once the program is installed and configured properly you will be free to use the evaluator!
Some examples of its utilization include the following:

### Ex 1) Simple addition:
input: 3 + 5
output: 8

### Ex 2) Parenthesis and Multiplication:
input: (2 + 3) * 4
output: 20

### Ex 3) Division by Zero:
input: 1 / 0
output: Error: Division by Zero

### Ex 4) Exponentiation:
input: 2 ** 3
output: 8

### Ex 5) Unmatched Parenthesis:
input (5 + 2
output: Error: Unmatched Parenthesis


The program handles a variety of errors such as:
    1. Division by Zero
    2. Unmatched Parenthesis
    3. Invalid Syntax
When such errors are detected it will return a descriptive message regarding your error.

