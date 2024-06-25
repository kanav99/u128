import sys

a = eval(input())
b = eval(input())
c = eval(input())

a = a[0] * (1<<64) + a[1]
b = b[0] * (1<<64) + b[1]
c = c[0] * (1<<64) + c[1]

prod = (a*b) % (1<<128)
assert prod == c
