# Интерпретатор
# **Грамматика языка**
```
Programm -> DeclareVar Describing

Describing -> BEGIN (ListAssigments | Read | Case | Write) END
DeclareVar -> VAR ListVar : integer;

ListVar -> Identifier {, Identifier}*

ListAssigments -> Assigment {, Assigment}*

Assigment -> Identifier = Exprassion;

Exprassion -> UnaryOp MathExprassion | MathExprassion
MathExprassion -> (Exprassion) | Operand | MathExprassion | BinaryOp | MathExprassion
UnaryOp -> -

BinaryOp -> +|-|/

Operand -> Identifier | Const

Read -> READ(ListVar);

Case -> CASE Exprassion OF ListChoice END_CASE;

ListChoice -> Choice {, Choice}*

Choice -> Const:Assigment

Write -> WRITE(ListVar);

Identifier -> [a-zA-z] Indetifier | [a-zA-z]

Const -> [@-9] Const | [@-9]

WS -> [ \t\n\r]+ -> skip

Vir= {6-97 to i/ a2 AZ)

Va = {Programm, Describing, DeclareVar, ListVar, ListAssigments, Assigment, Exprassion,
MathExprassion, UnaryOp, BinaryOp, Operand, Read, Case, ListChoice, Choice, Write
Identifier, Const}
```
# **Примеры программ**
### 1.
```
PROGRAM test;
VAR a,b,c,f,d,gddsdsdff,s,a:INTEGER;
BEGIN
    READ(f); READ(c);
    CASE f OF
        -50:
            f:=c * -50;
        2:
            f:=c*2;
        -10:
            f:=c*(-(-10+40));
    END_CASE
    a:=f + 10;
    f := a * 2;
    WRITE(a, f);
END

Input:
-10
10
Output:
-290 -580
```

### 2.
```
PROGRAM rect;
VAR a,b,c,f,d,command, result:INTEGER;
BEGIN
    READ(a,b);
    READ(command);
    CASE command OF
        1:
            result:=a * b;
        2:
            result:=a*2 + b*2;
    END_CASE
    WRITE(result);
END

Input:
10
5
1
Output
50

Input:
10
4
2
Output
28
```


### 3.
```
PROGRAM expr;
VAR a,b,c,f,d,command, result:INTEGER;
BEGIN
    READ(a,b);
    result:=(a+b * (8 + a * 10 - (b / 5 + 2)/10)) * (10 -(-a+50-10));
    WRITE(result);
END

Input:
1234
234
Output:
-815732376
```


# **Запуск**
###  `0. mkdir build`
### `1. cd build`
### `2. cmake ..`
### `3. make`
### `4. ./Translator --file=load_to_file`

# **Запуск в докер контейнере**
### `docker run -v "$(pwd)"/program.txt:/app/program.txt  -it --rm interpretator:1`
