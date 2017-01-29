# Cryptarithmetic

Solve cryptarithmetic problems using brute-force method.

By: Daniel 13515071

## Compile

This project can be compiled on Linux, or another UNIX-like system.

```
$ make
```

## Execute

This is sample of program execution on Intel(R) Processor 5Y10 CPU @ 0.80GHz,
Bash on Ubuntu on Windows.

Standard search:

```
$ bin/main -i case/case.txt
Crypt-Arithmetic by Daniel (13515071)

SEND + MORE = MONEY (9567 + 1085 = 10652)
Solution found in 62 ms

JUNE + JULY = APRIL (8432 + 8475 = 16907)
Solution found in 62 ms

FORTY + TEN + TEN = SIXTY (29786 + 850 + 850 = 31486)
Solution found in 156 ms

NUMBER + NUMBER = PUZZLE (201689 + 201689 = 403378)
Solution found in 125 ms

TILES + PUZZLES = PICTURE (91542 + 3077542 = 3169084)
Solution found in 62 ms

CLOCK + TICK + TOCK = PLANET (90892 + 6592 + 6892 = 104376)
Solution found in 93 ms

COCA + COLA = OASIS (8186 + 8106 = 16292)
Solution found in 0 ms

HERE + SHE = COMES (9454 + 894 = 10348)
Solution found in 0 ms

DOUBLE + DOUBLE + TOIL = TROUBLE (798064 + 798064 + 1936 = 1598064)
Solution found in 62 ms

NO + GUN + NO = HUNT (87 + 908 + 87 = 1082)
Solution found in 15 ms

THREE + THREE + TWO + TWO + ONE = ELEVEN (84611 + 84611 + 803 + 803 + 391 = 171219)
Solution found in 31 ms

CROSS + ROADS = DANGER (96233 + 62513 = 158746)
Solution found in 46 ms

MEMO + FROM = HOMER (8485 + 7358 = 15843)
Solution found in 0 ms
```

Complete search:

```
$ bin/main -e -i case/case.txt
Crypt-Arithmetic by Daniel (13515071)

SEND + MORE = MONEY (9567 + 1085 = 10652)
1 solution(s) in 125 ms

JUNE + JULY = APRIL (8432 + 8475 = 16907)
JUNE + JULY = APRIL (8532 + 8564 = 17096)
JUNE + JULY = APRIL (9253 + 9207 = 18460)
JUNE + JULY = APRIL (8524 + 8539 = 17063)
JUNE + JULY = APRIL (7924 + 7906 = 15830)
JUNE + JULY = APRIL (8534 + 8562 = 17096)
JUNE + JULY = APRIL (8435 + 8472 = 16907)
JUNE + JULY = APRIL (7926 + 7904 = 15830)
JUNE + JULY = APRIL (5486 + 5437 = 10923)
JUNE + JULY = APRIL (9257 + 9203 = 18460)
JUNE + JULY = APRIL (5487 + 5436 = 10923)
JUNE + JULY = APRIL (8529 + 8534 = 17063)
12 solution(s) in 296 ms

FORTY + TEN + TEN = SIXTY (29786 + 850 + 850 = 31486)
1 solution(s) in 234 ms

NUMBER + NUMBER = PUZZLE (201689 + 201689 = 403378)
1 solution(s) in 171 ms

TILES + PUZZLES = PICTURE (91542 + 3077542 = 3169084)
1 solution(s) in 218 ms

CLOCK + TICK + TOCK = PLANET (90892 + 6592 + 6892 = 104376)
1 solution(s) in 359 ms

COCA + COLA = OASIS (8186 + 8106 = 16292)
1 solution(s) in 0 ms

HERE + SHE = COMES (9454 + 894 = 10348)
1 solution(s) in 31 ms

DOUBLE + DOUBLE + TOIL = TROUBLE (798064 + 798064 + 1936 = 1598064)
1 solution(s) in 140 ms

NO + GUN + NO = HUNT (87 + 908 + 87 = 1082)
1 solution(s) in 15 ms

THREE + THREE + TWO + TWO + ONE = ELEVEN (84611 + 84611 + 803 + 803 + 391 = 171219)
1 solution(s) in 218 ms

CROSS + ROADS = DANGER (96233 + 62513 = 158746)
1 solution(s) in 140 ms

MEMO + FROM = HOMER (8485 + 7358 = 15843)
1 solution(s) in 0 ms
```
