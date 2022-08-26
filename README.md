# simple basic

## About

* Simple basic interpreter which runns on Nucleo STM32F072 and MacOS

## Spec

* `if`, `goto` and a-z variables are available in scripts
* `new`, `list`, `mem` and `run` are available in interactive mode
* variables are 32bit signed integers
* `+`, `-`, `*`, `/`, `%` are supported
* expression evaluation only has 64 nodes (`MAX_NODES`) to make a temporary parse tree for condtion in `if`
* basic line number must be between 1 and 65535 (inclusive)
* max characters per line is 255 exclude the last '\0'
* max basic program storage is 8192 (`MAX_BASMEM`)
* please refer to `test.bas` and `test2.bas` for more details

## Unit Test Requirements

* install `check` at <https://libcheck.github.io/check/web/install.html>

## Example

```
clang -std=c17 -Wall -g -O0 -I. -I/opt/homebrew/include /Users/scott/tmp/hoge/main.o /Users/scott/tmp/hoge/basic.o -o ~/tmp/hoge/bas
~/tmp/hoge/bas < test2.bas
> line:1, a=1
> line:2, if a%15 goto  11
> line:3, print "fizzbuzz"
> line:4, goto 51
> line:11, if a%3 goto 21
> line:12, print "fizz"
> line:13, goto 51
> line:21, if a%5 goto 50
> line:22, print "buzz"
> line:23, goto 51
> line:50, print a
> line:51, a=a+1
> line:52, if a-31 goto 2
> line:53, goto 100
> 1
2
fizz
4
buzz
fizz
7
8
fizz
buzz
11
fizz
13
14
fizzbuzz
16
17
fizz
19
buzz
fizz
22
23
fizz
buzz
26
fizz
28
29
fizzbuzz
> mem used: 184
mem free: 8008
>
```
