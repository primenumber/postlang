# postlang
Post correspondence problem(PCP) based esoteric programming language(?)

# syntax

Any even lines text file are accepted.

# compile

Source code has `2N` lines.
Compiler makes `N` dominos, each domino from `2i`-th line and `2i+1`-th line.
Compiler solves the PCP.
The PCP may have several answers, compiler chooses shotest answer.
If there are multiple shotest answers, compiler chooses first one in lexicographically.
Compiler filter `0` and `1` from the answer string, and assume it binary sequence, output the binary sequence.
If the length of the binary sequence is not multiple of 8, compiler report error.

# example

Complier outputs a text file written `Hello, World!`

```
0001001010100110001101100011011011110110001101000000010011101010111101100100111000110110001001101000010001010000
0001001010100110001101100011011011110110001101000000010011101010111101100100111000110110001001101000010001010000
```

