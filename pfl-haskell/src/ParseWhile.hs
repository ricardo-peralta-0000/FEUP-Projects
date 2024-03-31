-- Part 2
module ParseWhile where
-- Represents a program as a list of statements
import System.IO
import Control.Monad
import Text.ParserCombinators.Parsec
import Text.Parsec.String
import Text.ParserCombinators.Parsec.Expr
import Text.ParserCombinators.Parsec.Language
import qualified Text.ParserCombinators.Parsec.Token as Token
import Text.Parsec (parse, ParseError)
------------------------------------------------------------------------------------------------------------------------
-- Grammar
------------------------------------------------------------------------------------------------------------------------
{-
a ::= n | x | a opa a 
b ::= true | false | not b | b opb b | a opr a
-- Arithmetic, boolean and relational operators
opa ::= + | - | *
opb ::= and | =
opr ::= = | <= | ==
-- Statements definitions
s ::= x := a | skip | s1 ; s2 |(s) | if b then s1 else s2 | while b do s

-}

-- Lexer
languageDef = 
    emptyDef {
        Token.identStart = letter,
        Token.identLetter = alphaNum,
        Token.reservedNames = ["if","then","else","while","do","skip","True","False","not","and"],
        Token.reservedOpNames = ["+","-","*",":=","=" ,"==","<=","and","not"]
    }

lexer = Token.makeTokenParser languageDef
identifier = Token.identifier lexer -- parses an identifier
reserved   = Token.reserved   lexer -- parses a reserved name
reservedOp = Token.reservedOp lexer -- parses an operator
parens     = Token.parens     lexer -- parses surrounding parenthesis
                                    --   parens p
                                    -- takes care of the parenthesis and
                                    -- uses p to parse what's inside them
integer    = Token.integer    lexer -- parses an integer
semi       = Token.semi       lexer -- parses a semicolon
whiteSpace = Token.whiteSpace lexer -- parses whitespace

-- Removes the whitespace from the beginning of the string
whileParser :: Parser Stmt
whileParser = whiteSpace >> statement

------------------------------------------------------------------------------------------------------------------------
-- Data types
------------------------------------------------------------------------------------------------------------------------

data ABinOp 
    = Add 
    | Subtract 
    | Multiply 
    deriving (Show)

data BBinOp 
    = And 
    | BEqual
    deriving (Show)

data RBinOp 
    = Equal 
    | LessOrEqual 
    deriving (Show)

data AExpr 
    = Var String
    | IntConst Integer
    | ABinary ABinOp AExpr AExpr
    deriving (Show)

data BExpr 
    = BoolConst Bool
    | Not BExpr
    | BBinary BBinOp BExpr BExpr
    | RBinary RBinOp AExpr AExpr
    deriving (Show)

data Stmt 
    = Seq [Stmt]
    | Assign String AExpr
    | If BExpr Stmt Stmt
    | While BExpr Stmt
    | Skip
    deriving (Show)
------------------------------------------------------------------------------------------------------------------------
-- Parser
------------------------------------------------------------------------------------------------------------------------
-- Defines a statement surrounded by parenthesis or a sequence of statements
statement :: Parser Stmt
statement =   parens statement
          <|> sequenceOfStmt

-- Parses a statement
statement' :: Parser Stmt
statement' = try ifStmt
           <|> (try whileStmt)
           <|> skipStmt
           <|> assignStmt
           <|> (parens statement)
           -- <|> (eof >> return Skip)

-- Parses a sequence of statements
sequenceOfStmt :: Parser Stmt
sequenceOfStmt = do
    --list <- (endBy statement' semi)
    list <- (sepEndBy statement' semi)
    -- If there is only one statement, return it without using Seq
    return $ if length list == 1 then head list else Seq list

-- Parses an if statement
ifStmt :: Parser Stmt
ifStmt = do
    reserved "if"
    cond <- bExpression
    reserved "then"
    stmt1 <- statement
    reserved "else"
    stmt2 <- statement'
    return $ If cond stmt1 stmt2

-- Parses a while statement
whileStmt :: Parser Stmt
whileStmt = do 
    reserved "while"
    cond <- bExpression
    reserved "do"
    stmt <- statement
    return $ While cond stmt

-- Parses an assignment statement
assignStmt :: Parser Stmt
assignStmt = do
    var <- identifier
    reservedOp ":="
    expr <- aExpression
    return $ Assign var expr

-- Parses a skip statement
skipStmt :: Parser Stmt
skipStmt = reserved "skip" >> return Skip

-- Parses a boolean expression
bExpression :: Parser BExpr
bExpression = buildExpressionParser bOperators bTerm

-- Parses an arithmetic expression
aExpression :: Parser AExpr
aExpression = buildExpressionParser aOperators aTerm

-- Parses a relational expression
rExpression :: Parser BExpr
rExpression = do
    a1 <- aExpression
    op <- relation
    a2 <- aExpression
    return $ RBinary op a1 a2

-- Parses a relational operator
relation :: Parser RBinOp
relation =   (reservedOp "=" >> return Equal)
         <|> (reservedOp "<=" >> return LessOrEqual)
         <|> (reservedOp "==" >> return Equal)

--Lists with the operators precedence and associativity
-- Arithmetic operators
aOperators = [ [Infix  (reservedOp "*"   >> return (ABinary Multiply)) AssocLeft]
             , [Infix  (reservedOp "+"   >> return (ABinary Add))      AssocLeft,
                Infix  (reservedOp "-"   >> return (ABinary Subtract)) AssocLeft]
             ]

-- Boolean operators
bOperators = [ [Prefix (reservedOp "not" >> return (Not))]
             , [Infix  (reservedOp "="   >> return (BBinary BEqual)) AssocLeft]
             , [Infix  (reservedOp "and" >> return (BBinary And)) AssocLeft]
             ]

-- Parses an arithmetic term
aTerm =   parens aExpression
      <|> liftM Var identifier
      <|> liftM IntConst integer

-- Parses a boolean term
bTerm =   parens bExpression
      <|> (reserved "True"  >> return (BoolConst True ))
      <|> (reserved "False" >> return (BoolConst False))
      <|> (try rExpression)

------------------------------------------------------------------------------------------------------------------------
-- Parser function
------------------------------------------------------------------------------------------------------------------------
-- Parses a string
parseString :: String -> Stmt
parseString str =
    case parse whileParser "" str of
        Left e  -> error "Run-time error"
        Right r -> r
    where
        whileParser = whiteSpace >> statement