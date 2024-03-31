-- PFL 2023/24 - Haskell practical assignment
import Structures
import Data.Char (isSpace, isDigit, isAlpha)
import ParseWhile


-- Part 1

-- Do not modify our definition of Inst and Code
data Inst =
  Push Integer | Add | Mult | Sub | Tru | Fals | Equ | Le | And | Neg | Fetch String | Store String | Noop |
  Branch Code Code | Loop Code Code
  deriving Show
type Code = [Inst]

-- createEmptyStack :: Stack
-- stack2Str :: Stack -> String
-- Defined in Stack.hs

-- createEmptyState :: State
-- state2Str :: State -> String
-- Defined in State.hs

run :: (Code, Stack, State) -> (Code, Stack, State)
-- Base case: empty code
run ([], stack, state) = ([], stack, state)
run (code, stack, state) = case head code of
  -- Push
  Push n -> run (tail code, push (IntValue n) stack, state)
  -- Add
  Main.Add -> run (tail code, push (IntValue (applyArithOp Main.Add (top stack) (top (pop stack)))) (pop (pop stack)), state)
  -- Mult
  Main.Mult -> run (tail code, push (IntValue (applyArithOp Mult (top stack) (top (pop stack)))) (pop (pop stack)), state)
  -- Sub
  Main.Sub -> run (tail code, push (IntValue (applyArithOp Sub (top stack) (top (pop stack)))) (pop (pop stack)), state)
  -- Tru
  Tru -> run (tail code, push (BoolValue True) stack, state)
  -- Fals
  Fals -> run (tail code, push (BoolValue False) stack, state)
  -- Equ
  Equ -> run (tail code, push (BoolValue (applyBoolOp Equ (top stack) (top (pop stack)))) (pop (pop stack)), state)
  -- Le
  Le -> run (tail code, push (BoolValue (applyBoolOp Le (top (pop stack)) (top stack))) (pop (pop stack)), state)
  -- And
  Main.And -> run (tail code, push (BoolValue (applyBoolOp Main.And (top stack) (top (pop stack)))) (pop (pop stack)), state)
  -- Neg
  Neg -> run (tail code, push (BoolValue (not (getBoolValue (top stack)))) (pop stack), state)
  -- Fetch
  Fetch x -> run (tail code, push ((get x state)) stack, state)
  -- Store
  Store x -> run (tail code, pop stack, set x (top stack) state)
  -- Noop
  Noop -> run (tail code, stack, state)
  -- Branch
  Branch c1 c2 -> case top stack of
    -- True
    BoolValue True -> run (c1 ++ (tail code), pop stack, state)
    -- False
    BoolValue False -> run (c2 ++ (tail code), pop stack, state)
    -- Otherwise
    _ -> error "Run-time error"
  -- Loop
  Loop c1 c2 -> run (c1 ++ [Branch (c2 ++ [Loop c1 c2]) [Noop]] ++ (tail code), stack, state)
  


-- Helper functions for operations
applyArithOp :: Inst -> Value -> Value -> Integer
applyArithOp Main.Add (IntValue v1) (IntValue v2) = v1 + v2
applyArithOp Mult (IntValue v1) (IntValue v2) = v1 * v2
applyArithOp Sub (IntValue v1) (IntValue v2) = v1 - v2
applyArithOp _ _ _ = error "Run-time error"

applyBoolOp :: Inst -> Value -> Value -> Bool
applyBoolOp Equ (IntValue v1) (IntValue v2) = v1 == v2
applyBoolOp Equ (BoolValue v1) (BoolValue v2) = v1 == v2
applyBoolOp Le (IntValue v1) (IntValue v2) = v2 <= v1
applyBoolOp Main.And (BoolValue v1) (BoolValue v2) = v1 && v2
applyBoolOp _ _ _ = error "Run-time error"


-- To help you test your assembler
testAssembler :: Code -> (String, String)
testAssembler code = (stack2Str stack, state2Str state)
  where (_,stack,state) = run(code, createEmptyStack, createEmptyState)

-- Examples:
-- testAssembler [Push 10,Push 4,Push 3,Sub,Mult] == ("-10","")
-- testAssembler [Fals,Push 3,Tru,Store "var",Store "a", Store "someVar"] == ("","a=3,someVar=False,var=True")
-- testAssembler [Fals,Store "var",Fetch "var"] == ("False","var=False")
-- testAssembler [Push (-20),Tru,Fals] == ("False,True,-20","")
-- testAssembler [Push (-20),Tru,Tru,Neg] == ("False,True,-20","")
-- testAssembler [Push (-20),Tru,Tru,Neg,Equ] == ("False,-20","")
-- testAssembler [Push (-20),Push (-21), Le] == ("True","")
-- testAssembler [Push 5,Store "x",Push 1,Fetch "x",Sub,Store "x"] == ("","x=4")
-- testAssembler [Push 10,Store "i",Push 1,Store "fact",Loop [Push 1,Fetch "i",Equ,Neg] [Fetch "i",Fetch "fact",Mult,Store "fact",Push 1,Fetch "i",Sub,Store "i"]] == ("","fact=3628800,i=1")
-- If you test:
-- testAssembler [Push 1,Push 2,And]
-- You should get an exception with the string: "Run-time error"
-- If you test:
-- testAssembler [Tru,Tru,Store "y", Fetch "x",Tru]
-- You should get an exception with the string: "Run-time error"

-- Part 2
-- Represents a program as a list of statements

{-
-- Arithmetic expressions
-- Aexp ::= n | x | Aexp + Aexp | Aexp - Aexp | Aexp * Aexp
-}
data Aexp
  = AConst Integer
  | AVar String
  | AAdd Aexp Aexp
  | ASub Aexp Aexp
  | AMult Aexp Aexp
  deriving Show

{-
-- Boolean expressions
-- Bexp ::= true | false | Aexp = Aexp | Aexp <= Aexp | not Bexp | Bexp and Bexp
-}
data Bexp
  = BTrue
  | BFalse
  | BEq Aexp Aexp
  | BXor Bexp Bexp
  | BLe Aexp Aexp
  | BNot Bexp
  | BAnd Bexp Bexp
  deriving Show

{-
-- Statements
-- Used to represent the program
-- One can make assignments, execute statements sequentially, make conditional statements and loops
-}
data Stm
  = Assignment String Aexp    -- x := Aexp
  | Sequence [Stm]            -- Stm; Stm; ...; Stm
  | IfThenElse Bexp Stm Stm   -- if Bexp then Stm else Stm
  | While Bexp Stm            -- while Bexp do Stm
  deriving Show

-- Auxiliary functions

-- Arithmetic expressions
-- compA :: Aexp -> Code
compA :: Aexp -> Code
compA (AConst n) = [Push n]
compA (AVar x) = [Fetch x]
compA (AAdd a1 a2) = compA a1 ++ compA a2 ++ [Main.Add]
compA (ASub a1 a2) = compA a2 ++ compA a1 ++ [Sub]
compA (AMult a1 a2) = compA a1 ++ compA a2 ++ [Mult]

-- Boolean expressions
-- compB :: Bexp -> Code
compB :: Bexp -> Code
compB BTrue = [Tru]
compB BFalse = [Fals]
compB (BEq a1 a2) = compA a1 ++ compA a2 ++ [Equ]
compB (BLe a1 a2) = compA a2 ++ compA a1 ++ [Le]
compB (BNot b) = compB b ++ [Neg]
compB (BAnd b1 b2) = compB b1 ++ compB b2 ++ [Main.And]
compB (BXor b1 b2) = compB b1 ++ compB b2 ++ [Equ]

-- Converts imperative programs to machine code defined by Inst and Code
-- compile :: Program -> Code
compile :: [Stm] -> Code
compile [] = []
compile (stmt:stmts) = case stmt of
  Assignment var expr -> compA expr ++ [Store var] ++ compile stmts
  Sequence stmtSeq -> compile stmtSeq ++ compile stmts
  IfThenElse condStmt thenStmt elseStmt ->
    compB condStmt ++ [Branch (compile [thenStmt]) (compile [elseStmt])] ++ compile stmts
  Main.While condStmt bodyStmt ->
    [Loop (compB condStmt) (compile [bodyStmt] ++ [Noop])] ++ compile stmts

-- Parser
-- Parses a string into a list of statements
parse :: String -> [Stm]
parse = buildData . parseString

--Examples Parse String
-- parseString "" 
-- Seq []
-- parseString "x := 5; x := x - 1;" 
-- Seq [Assign "x" (IntConst 5),Assign "x" (ABinary Subtract (Var "x") (IntConst 1))]
-- parseString "x := 0 - 2;" 
-- Assign "x" (ABinary Subtract (IntConst 0) (IntConst 2))
-- parseString "if (not True and 2 <= 5 = 3 == 4) then x :=1; else y := 2;"
-- If (BBinary And (Not (BoolConst True)) (BBinary BEqual (RBinary LessOrEqual (IntConst 2) (IntConst 5)) (RBinary Equal (IntConst 3) (IntConst 4)))) (Assign "x" (IntConst 1)) (Assign "y" (IntConst 2))
-- parseString "x := 42; if x <= 43 then x := 1; else (x := 33; x := x+1;);"
-- Seq [Assign "x" (IntConst 42),If (RBinary LessOrEqual (Var "x") (IntConst 43)) (Assign "x" (IntConst 1)) (Seq [Assign "x" (IntConst 33),Assign "x" (ABinary Add (Var "x") (IntConst 1))])]
-- parseString "x := 42; if x <= 43 then x := 1; else x := 33; x := x+1;"
-- Seq [Assign "x" (IntConst 42),If (RBinary LessOrEqual (Var "x") (IntConst 43)) (Assign "x" (IntConst 1)) (Assign "x" (IntConst 33)),Assign "x" (ABinary Add (Var "x") (IntConst 1))]
-- parseString "x := 42; if x <= 43 then x := 1; else x := 33; x := x+1; z := x+x;"
-- Seq [Assign "x" (IntConst 42),If (RBinary LessOrEqual (Var "x") (IntConst 43)) (Assign "x" (IntConst 1)) (Assign "x" (IntConst 33)),Assign "x" (ABinary Add (Var "x") (IntConst 1)),Assign "z" (ABinary Add (Var "x") (Var "x"))]
-- parseString "x := 44; if x <= 43 then x := 1; else (x := 33; x := x+1;); y := x*2;"
-- Seq [Assign "x" (IntConst 44),If (RBinary LessOrEqual (Var "x") (IntConst 43)) (Assign "x" (IntConst 1)) (Seq [Assign "x" (IntConst 33),Assign "x" (ABinary Add (Var "x") (IntConst 1))]),Assign "y" (ABinary Multiply (Var "x") (IntConst 2))]
-- parseString "x := 42; if x <= 43 then (x := 33; x := x+1;) else x := 1;" 
-- Seq [Assign "x" (IntConst 42),If (RBinary LessOrEqual (Var "x") (IntConst 43)) (Seq [Assign "x" (IntConst 33),Assign "x" (ABinary Add (Var "x") (IntConst 1))]) (Assign "x" (IntConst 1))]
-- parseString "if (1 == 0+1 = 2+1 == 3) then x := 1; else x := 2;" 
-- If (BBinary BEqual (RBinary Equal (IntConst 1) (ABinary Add (IntConst 0) (IntConst 1))) (RBinary Equal (ABinary Add (IntConst 2) (IntConst 1)) (IntConst 3))) (Assign "x" (IntConst 1)) (Assign "x" (IntConst 2))
-- parseString "if (1 == 0+1 = (2+1 == 4)) then x := 1; else x := 2;" 
-- If (BBinary BEqual (RBinary Equal (IntConst 1) (ABinary Add (IntConst 0) (IntConst 1))) (RBinary Equal (ABinary Add (IntConst 2) (IntConst 1)) (IntConst 4))) (Assign "x" (IntConst 1)) (Assign "x" (IntConst 2))
-- parseString "x := 2; y := (x - 3)*(4 + 2*3); z := x +x*(2);" 
-- Seq [Assign "x" (IntConst 2),Assign "y" (ABinary Multiply (ABinary Subtract (Var "x") (IntConst 3)) (ABinary Add (IntConst 4) (ABinary Multiply (IntConst 2) (IntConst 3)))),Assign "z" (ABinary Add (Var "x") (ABinary Multiply (Var "x") (IntConst 2)))]
-- parseString "i := 10; fact := 1; while (not(i == 1)) do (fact := fact * i; i := i - 1;);" 
-- Seq [Assign "i" (IntConst 10),Assign "fact" (IntConst 1),While (Not (RBinary Equal (Var "i") (IntConst 1))) (Seq [Assign "fact" (ABinary Multiply (Var "fact") (Var "i")),Assign "i" (ABinary Subtract (Var "i") (IntConst 1))])]


buildData :: Stmt -> [Stm]
buildData (Seq stmts) = concatMap buildData stmts
buildData (Assign var expr) = [Assignment var (convertAExpr expr)]
buildData (If cond thenStmt elseStmt) =
  [IfThenElse (convertBExpr cond) (Sequence (buildData thenStmt)) (Sequence (buildData elseStmt))]
buildData (ParseWhile.While cond bodyStmt) =
  [Main.While (convertBExpr cond) (Sequence (buildData bodyStmt))]
buildData Skip = []

convertAExpr :: AExpr -> Aexp
convertAExpr (Var x) = AVar x
convertAExpr (IntConst n) = AConst n
convertAExpr (ABinary op a1 a2) = case op of
  ParseWhile.Add -> AAdd (convertAExpr a1) (convertAExpr a2)
  Subtract -> ASub (convertAExpr a1) (convertAExpr a2)
  Multiply -> AMult (convertAExpr a1) (convertAExpr a2)

convertBExpr :: BExpr -> Bexp
convertBExpr (BoolConst b) = if b then BTrue else BFalse
convertBExpr (Not b) = BNot (convertBExpr b)
convertBExpr (BBinary ParseWhile.And b1 b2) = BAnd (convertBExpr b1) (convertBExpr b2)
convertBExpr (BBinary BEqual b1 b2) = BXor (convertBExpr b1) (convertBExpr b2)
convertBExpr (RBinary Equal a1 a2) = BEq (convertAExpr a1) (convertAExpr a2)
convertBExpr (RBinary LessOrEqual a1 a2) = BLe (convertAExpr a1) (convertAExpr a2)


-- Examples:
-- testParser "x := 5; x := x - 1;" == ("","x=4")
-- testParser "x := 0 - 2;" == ("","x=-2")
-- testParser "if (not True and 2 <= 5 = 3 == 4) then x :=1; else y := 2;" == ("","y=2")
-- testParser "x := 42; if x <= 43 then x := 1; else (x := 33; x := x+1;);" == ("","x=1")
-- testParser "x := 42; if x <= 43 then x := 1; else x := 33; x := x+1;" == ("","x=2")
-- testParser "x := 42; if x <= 43 then x := 1; else x := 33; x := x+1; z := x+x;" == ("","x=2,z=4")
-- testParser "x := 44; if x <= 43 then x := 1; else (x := 33; x := x+1;); y := x*2;" == ("","x=34,y=68")
-- testParser "x := 42; if x <= 43 then (x := 33; x := x+1;) else x := 1;" == ("","x=34")
-- testParser "if (1 == 0+1 = 2+1 == 3) then x := 1; else x := 2;" == ("","x=1")
-- testParser "if (1 == 0+1 = (2+1 == 4)) then x := 1; else x := 2;" == ("","x=2")
-- testParser "x := 2; y := (x - 3)*(4 + 2*3); z := x +x*(2);" == ("","x=2,y=-10,z=6")
-- testParser "i := 10; fact := 1; while (not(i == 1)) do (fact := fact * i; i := i - 1;);" == ("","fact=3628800,i=1")

-- To help you test your parser
testParser :: String -> (String, String)
testParser programCode = (stack2Str stack, state2Str state)
  where (_,stack,state) = run(compile (parse programCode), createEmptyStack, createEmptyState)

exampleProgram :: [Stm]
exampleProgram = [IfThenElse
  (BAnd (BNot BTrue) (BAnd (BLe (AConst 2) (AConst 5)) (BEq (AConst 3) (AConst 4))))
  (Assignment "x" (AConst 1))
  (Assignment "y" (AConst 2))]

exampleProgram2 :: [Stm]
exampleProgram2 = [Assignment "x" (AConst 5), Assignment "x" (ASub (AVar "x") (AConst 1))]
exampleProgram3 :: [Stm]
-- loop example
exampleProgram3 = [Assignment "i" (AConst 10), Assignment "fact" (AConst 1), Main.While (BNot (BEq (AVar "i") (AConst 1))) (Sequence [Assignment "fact" (AMult (AVar "fact") (AVar "i")), Assignment "i" (ASub (AVar "i") (AConst 1))])]

compiledCode :: Code
compiledCode = compile exampleProgram
compiledCode2 :: Code
compiledCode2 = compile exampleProgram2
compiledCode3 :: Code
compiledCode3 = compile exampleProgram3


testCases :: [(String, (String, String))]
testCases = [
    ("x := 5; x := x - 1;", ("","x=4")),
    ("x := 0 - 2;", ("","x=-2")),
    ("if (not True and 2 <= 5 = 3 == 4) then x :=1; else y := 2;", ("","y=2")),
    ("x := 42; if x <= 43 then x := 1; else (x := 33; x := x+1;);", ("","x=1")),
    ("x := 42; if x <= 43 then x := 1; else x := 33; x := x+1;", ("","x=2")),
    ("x := 42; if x <= 43 then x := 1; else x := 33; x := x+1; z := x+x;", ("","x=2,z=4")),
    ("x := 44; if x <= 43 then x := 1; else (x := 33; x := x+1;); y := x*2;", ("","x=34,y=68")),
    ("x := 42; if x <= 43 then (x := 33; x := x+1;) else x := 1;", ("","x=34")),
    ("if (1 == 0+1 = 2+1 == 3) then x := 1; else x := 2;", ("","x=1")),
    ("if (1 == 0+1 = (2+1 == 4)) then x := 1; else x := 2;", ("","x=2")),
    ("x := 2; y := (x - 3)*(4 + 2*3); z := x +x*(2);", ("","x=2,y=-10,z=6")),
    ("i := 10; fact := 1; while (not(i == 1)) do (fact := fact * i; i := i - 1;);", ("","fact=3628800,i=1"))
    ]

runTests :: [(String, (String, String))] -> IO ()
runTests [] = return ()
runTests ((input, expected):xs) = do
    let result = testParser input
    putStrLn $ "Input: " ++ input
    putStrLn $ "Expected: " ++ show expected
    putStrLn $ "Result: " ++ show result
    putStrLn $ "Test passed: " ++ show (result == expected)
    putStrLn "-------------------------"
    runTests xs

--main :: IO ()
--main = runTests testCases