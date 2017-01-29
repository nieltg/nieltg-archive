# DFAExec

Read DFA from file and ask for input to execute the DFA.

By: Daniel / 13515071

## Compilation

Compilation can be done on Linux or Windows using Bash on Ubuntu on Windows.

```
$ make
```

## Execution

### Normal Mode

Ask for user input, then exit.

```
$ bin/dfaexec -i case/dfa.txt
```

### Continuous Mode

Ask for user input, execute the DFA until user inputs a blank line.

```
$ bin/dfaexec -i case/dfa.txt
```
