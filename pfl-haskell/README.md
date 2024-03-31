# TP2
> PFL 2023/24 - Haskell practical assignment
> 
> **Group T05_G04 :**
> - Ricardo Miguel Matos Oliveira Peralta  - *up202206392*
> - António Guilherme Sanches de Magalhães Koch e Silva -  *up202108760*
> 
> **Contributions:**
> - Ricardo Peralta: 50%
> - António Silva: 50%

## Problem Description
In this assignment, we were expected to implement a short imperative language that would be compiled to a low-level machine with a configuration of the form `(c, e, s)`. 

> `c` is a list of instructions in our imperative language to be executed, `e` is the evaluation stack, and `s` is the storage.
The language supports arithmetic and boolean operations, as well as conditional `(if then else)` and iterative control structures`(while)`.

The machine operates with instructions such as **push-n**, **add**, **mult**, **sub**, **true**, **false**, **eq**, **le**, and others.

## How to Run the Project
The project can be run by loading the `main.hs` file in the Haskell interpreter and calling the `main` function. The `main` function will run the tests and display the results.
**Before** running the project, please uncomment the definition of the `main` function in the end of the `main.hs` file.
Bellow a list of the commands to setup and run the project:
```bash
# Unzip the project
unzip PFL_TP2_T05_G04.zip

# Change directory to the project folder
cd PFL_TP2_T05_G04

# Load the main module in the Haskell interpreter
ghci src/main.hs

# Run the main function
main
```

## Implementation Summary

This project is implemented in Haskell and consists of several modules:

- [`main.hs`](src/main.hs): This is the main module of the project. It contains the main functionality and ties together the other modules.
  - **Part 1:**
  
    The first part of the project involves creating a low-level machine with specific instructions and operations. Instructions include arithmetic and boolean operations, stack manipulation, and flow control. 
    The goal is to implement functions for creating an empty stack and state, converting stack and state to strings, and running a program on the machine.

    ```haskell
    -- We made use of the already defined data types to implement the low-level machine commands.
    type Code = [Inst]
    -- This commands have a corresponding action in the machine, being run by the run function.
    run :: (Code, Stack, State) -> (Code, Stack, State)
    -- Helper functions used by run
    applyArithOp :: Inst -> Value -> Value -> Integer
    applyBoolOp :: Inst -> Value -> Value -> Bool
    ```

  - **Part 2:**
  
    In the second part of the project, a compiler is implemented to translate programs in a imperative language defined in the **Specification** guide into lists of instructions for the low-level machine defined in part 1. 
    Additionally, a parser needs to be developed to transform imperative programs represented as strings into a corresponding abstract syntax tree. The imperative language includes statements like assignments, sequences, if-then-else, and while loops.

    ```haskell
    -- Data type to convert the statements of the language into a list of instructions for the machine that will be passed as an argument to the run function (code).
    -- Aexp | Bexp | Stmt
    -- Compile is responsible for converting the statements of the language into a list of instructions for the machine.
    compile :: [Stm] -> Code
    -- Helper functions used by compile
    compA :: Aexp -> Code   -- Arithmetic expressions
    compB :: Bexp -> Code   -- Boolean expressions

    -- Parses a string into a list of statements
    parse :: String -> [Stm]
    parse = buildData . parseString
    -- Parse is a composition of buildData and parseString

    -- parseString is defined in the ParseWhile module

    -- buildData is responsible for converting the output of the parser into a list of statements
    buildData :: Stmt -> [Stm]
    ```


- [`ParseWhile.hs`](src/ParseWhile.hs): This module is responsible for parsing the language used in the project and is introduced as a string. It uses the Parsec library to parse the string and return Stmt, which is a data type that represents the statements of the language.
  
  A grammar was defined for ease of defining the language. The grammar is as follows:
    ```haskell
    -- Grammar for the language
    -- a ::= n | x | a opa a 
    -- b ::= true | false | not b | b opb b | a opr a
    -- Arithmetic, boolean and relational operators
    -- opa ::= + | - | *
    -- opb ::= and | =
    -- opr ::= = | <= | ==
    -- Statements definitions
    -- s ::= x := a | skip | s1 ; s2 |(s) | if b then s1 else s2 | while b do s
    ```
    The gramar is used to convert the string into a Stmt data type, which corresponds to an AST (Abstract Syntax Tree).

    ```haskell
    import System.IO
    import Control.Monad
    import Text.ParserCombinators.Parsec
    import Text.Parsec.String
    import Text.ParserCombinators.Parsec.Expr
    import Text.ParserCombinators.Parsec.Language
    import qualified Text.ParserCombinators.Parsec.Token as Token
    import Text.Parsec (parse, ParseError)

    -- Function that parses a string and returns a Stmt
    parseString :: String -> Stmt

    -- Data Types
    -- AExpr represents arithmetic expressions
    -- BExpr represents boolean expressions
    -- Stmt represents statements (if, while, seuqence, assign, skip)
    ```
    The internal workings of this module are the usual ones in functional parsing. We define a parser for each of the data types and then combine them to parse the string. We make use of the modules associated with the Parsec library to define the parsers.

- [`Structures.hs`](src/Structures.hs): This module defines the data structures used in the project. It defines the 'Stack' and 'Storage' data structures.
    ```haskell
    -- The Value data type is used to represent the values that can be stored in the stack. Can be either an integer or a boolean.
    data Value = IntValue Integer | BoolValue Bool
        deriving Show

    -- Stack is a list of values. Functions are defined to push and pop values from the stack as well as to handle empty stacks and get the top value of the stack.
    type Stack = [Value]

    -- Storage is a list of pairs of strings and values. This is used to store variables and their values. Functions are defined to get and set values in the storage.
    type State = [(String, Value)]
    ```



## Examples
Specific test cases were provided in the **TP2 - File Template**, which were used to test the implementation of the project. Additional specific test cases were also developed for testing various parts of the code during development.
For ease, the function `runTests` was defined in the main module, which runs the most relevant tests that cover the progam as a whole and its functionalities.
Bellow is displayed the output of the `runTests` function.

    ```bash 
    Input: x := 5; x := x - 1;
    Expected: ("","x=4")
    Result: ("","x=4")
    Test passed: True
    -------------------------
    Input: x := 0 - 2;
    Expected: ("","x=-2")
    Result: ("","x=-2")
    Test passed: True
    -------------------------
    Input: if (not True and 2 <= 5 = 3 == 4) then x :=1; else y := 2;
    Expected: ("","y=2")
    Result: ("","y=2")
    Test passed: True
    -------------------------
    Input: x := 42; if x <= 43 then x := 1; else (x := 33; x := x+1;);
    Expected: ("","x=1")
    Result: ("","x=1")
    Test passed: True
    -------------------------
    Input: x := 42; if x <= 43 then x := 1; else x := 33; x := x+1;
    Expected: ("","x=2")
    Result: ("","x=2")
    Test passed: True
    -------------------------
    Input: x := 42; if x <= 43 then x := 1; else x := 33; x := x+1; z := x+x;
    Expected: ("","x=2,z=4")
    Result: ("","x=2,z=4")
    Test passed: True
    -------------------------
    Input: x := 44; if x <= 43 then x := 1; else (x := 33; x := x+1;); y := x*2;
    Expected: ("","x=34,y=68")
    Result: ("","x=34,y=68")
    Test passed: True
    -------------------------
    Input: x := 42; if x <= 43 then (x := 33; x := x+1;) else x := 1;
    Expected: ("","x=34")
    Result: ("","x=34")
    Test passed: True
    -------------------------
    Input: if (1 == 0+1 = 2+1 == 3) then x := 1; else x := 2;
    Expected: ("","x=1")
    Result: ("","x=1")
    Test passed: True
    -------------------------
    Input: if (1 == 0+1 = (2+1 == 4)) then x := 1; else x := 2;
    Expected: ("","x=2")
    Result: ("","x=2")
    Test passed: True
    -------------------------
    Input: x := 2; y := (x - 3)*(4 + 2*3); z := x +x*(2);
    Expected: ("","x=2,y=-10,z=6")
    Result: ("","x=2,y=-10,z=6")
    Test passed: True
    -------------------------
    Input: i := 10; fact := 1; while (not(i == 1)) do (fact := fact * i; i := i - 1;);
    Expected: ("","fact=3628800,i=1")
    Result: ("","fact=3628800,i=1")
    Test passed: True
    -------------------------
    ```

## Conclusions
The interpreter developed adeptly handles the imperative language and low-level machine. The interpreter is easy to use and understand, and the design choices, such as using modules, a parser library and a well-structured AST, contribute to its readability. 
The interpreter correctly handles errors, triggering exception events that display runtime errors for an easier user experience.

Overall, the interpreter serves as a valuable tool for educational and experimental purposes, providing a solid foundation for further exploration in programming languages, compiler's design and functional parsing.

We are satisfied with the result of the project and the knowledge we gained from it. This project was a great opportunity to learn more about Haskell and functional programming in general.

### References
https://wiki.haskell.org/Parsing_a_simple_imperative_language
https://github.com/budabudimir/imp_interpreter/blob/master/IMP_Parser.hs
Slides from classes
