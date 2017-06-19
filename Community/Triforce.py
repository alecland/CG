import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

n = int(input())

# Write an action using print
# To debug: print("Debug messages...", file=sys.stderr)
for i in range (n):
    line = ''
    if (i == 0):
        line = '.'
        line += ' ' * (2 * (n - i) - 2)
        line += '*' * (1 + 2 * i)
    else:        
        line += ' ' * (2 * n - i - 1)
        line += '*' * (1 + 2 * i)
    print(line)
    
for i in range (n):
    line = ''
    line += ' ' * (n - i - 1)
    line += '*' * (1 + 2 * i)
    line += ' ' * (2 * (n - i) - 1)
    line += '*' * (1 + 2 * i)
    print(line)
