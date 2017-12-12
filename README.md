# Compiler
This repository contains a compiler that processes statements written in the C++ language programming.

## Requirements
To use the compiler it's recommended to use CLion IDE from jetBrains, but you can use another IDE.

## Introduction
The application consists in four stages wich are Lexical, sytactic, semantic analysis and Code generation.

### Lexical analysis
the lexical analizer reads every character from the input and assigns a token to it.

### Syntactic analysis
Then the syntactic uses a LR file to create a grammar and validate the input through rules. 

### Semantic analysis
Once the input is validated the semantic analyzer validates the data type and saves the variables and its type in a symbol table, so non declared variables can be used.
The semantic analizer creates a semantic tree to make easier the code generation, the semantic tree is displayed in the console in a XML style.

### Code generation
Finally the code generation takes the semantic tree and creates a .asm file with the resulting code.

### More information
The input and output files can be found in the cmake-build-debug folder, also the .lr file with the rules is there.

### Example

#### Input

<img src="https://github.com/JonathanVega08/Compiler/blob/master/img/Input.png"/>

#### Output
<img src="https://github.com/JonathanVega08/Compiler/blob/master/img/output.png"/>



