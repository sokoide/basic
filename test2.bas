1 a=1
2 if a%15 goto  11
3 print "fizzbuzz"
4 goto 51
11 if a%3 goto 21
12 print "fizz"
13 goto 51
21 if a%5 goto 50
22 print "buzz"
23 goto 51
50 print a
51 a=a+1
52 if a-31 goto 2
53 goto 100
run
mem
