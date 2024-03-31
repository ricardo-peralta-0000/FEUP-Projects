-- Stack.hs
module Structures(
    Stack,
    Value(..),
    createEmptyStack,
    push,
    pop,
    top,
    isEmpty,
    stack2Str,
    value2Str,
    getIntValue,
    getBoolValue,
    State,
    createEmptyState,
    get,
    set,
    isIn,
    state2Str
) where
import Data.List (intercalate, sortOn, intercalate)

-- Stack that accepts any type of value
-- Implemented using lists
type Stack = [Value]

data Value = IntValue Integer | BoolValue Bool
    deriving Show

-- Helper functions
getIntValue :: Value -> Integer
getIntValue (IntValue v) = v
getBoolValue :: Value -> Bool
getBoolValue (BoolValue v) = v


-- Stack Functions
createEmptyStack :: Stack
createEmptyStack = []

push :: Value -> Stack -> Stack
push v s = v:s

pop :: Stack -> Stack
pop [] = error "Run-time error"
pop (_:xs) = xs

top :: Stack -> Value
top [] = error "Run-time error"
top (x:_) = x

isEmpty :: Stack -> Bool
isEmpty [] = True
isEmpty _ = False

stack2Str :: Stack -> String
stack2Str stack = intercalate "," $ map value2Str stack

value2Str :: Value -> String
value2Str (IntValue v) = show v
value2Str (BoolValue v) = show v

-- tests for stack functions
-- createEmptyStack
-- push (IntValue 1) []
-- push (IntValue 1) [IntValue 2]
-- push (BoolValue True) []
-- push (BoolValue True) [BoolValue False]
-- pop []
-- pop [IntValue 1]
-- pop [IntValue 1, IntValue 2]
-- top []
-- top [IntValue 1]
-- top [IntValue 1, IntValue 2]
-- isEmpty []
-- isEmpty [IntValue 1]
-- isEmpty [IntValue 1, IntValue 2]
-- stack2Str []
-- stack2Str [IntValue 1]
-- stack2Str [IntValue 1, IntValue 2]
-- value2Str (IntValue 1)
-- value2Str (BoolValue True)

type State = [(String, Value)]

-- State Functions
-- createEmptyState :: State
createEmptyState :: State
createEmptyState = []

-- get function
get :: String -> State -> Value
get _ [] = error "Run-time error"
get x ((y, v):xs) = if x == y 
    then v 
    else get x xs

-- set function
set :: String -> Value -> State -> State
set x v [] = [(x, v)]
set x v ((y, v'):xs) = if x == y 
    then (x, v):xs 
    else (y, v'):(set x v xs)

-- is in function
isIn :: String -> State -> Bool
isIn _ [] = False
isIn x ((y, _):xs) = if x == y 
    then True 
    else isIn x xs

state2Str :: State -> String
state2Str state = intercalate "," $ map (\(var, val) -> var ++ "=" ++ valueToStr val) (sortOn fst state)
  where
    valueToStr (IntValue n) = show n
    valueToStr (BoolValue b) = show b

-- tests for state functions
-- get "x" [("x", 1), ("y", 2)]
-- get "y" [("x", 1), ("y", 2)]
-- set "x" 3 [("x", 1), ("y", 2)]
-- set "y" 4 [("x", 1), ("y", 2)]
-- isIn "x" [("x", 1), ("y", 2)]
-- isIn "y" [("x", 1), ("y", 2)]
-- isIn "z" [("x", 1), ("y", 2)]
-- state2Str [("x", 1), ("y", 2)]
-- state2Str [("y", 2), ("x", 1)]
-- state2Str [("x", 1)]
-- state2Str []

