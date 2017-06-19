import sys
import math
import binascii
import re

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

encrypt = input()
print(encrypt, file=sys.stderr)
bitmap = ''
decrypt = ''
is_invalid = False
is_answered = False

# Write an action using print
# To debug: print("Debug messages...", file=sys.stderr)

def text_from_bits(bits, encoding='utf-8', errors='surrogatepass'):
    n = int(bits, 2)
    return n.to_bytes((n.bit_length() + 7) // 8, 'big').decode(encoding, errors) or '\0'    

split_string = encrypt.split()

if (len(split_string) % 2 != 0):
    is_invalid = True

for i in range(len(split_string)):
    if (not split_string[i].isdigit()):
        is_invalid = True
        break
    if (i % 2 == 0):        
        if (split_string[i] == '0'):
            bitmap += '1'
        elif (split_string[i] == '00'):
            bitmap += '0'
        else:
            is_invalid = True
            break
    else:
        for j in range(len(split_string[i]) - 1):
            bitmap += bitmap[-1]
 
if(is_invalid):
    print('INVALID')
    is_answered = True
    
n = 0
while (n < len(bitmap) - 1):
    bitmap = bitmap[:n] + '0' + bitmap[n:]
    n += 8

if (not is_answered and len(bitmap) % 8 != 0):
    print('INVALID')
    is_answered = True
    
if (not is_answered):
    print(bitmap, file=sys.stderr)
    decrypt = text_from_bits(bitmap)
    print(decrypt, file=sys.stderr)

    if(not is_invalid):
        print(decrypt)
    else:
        print('INVALID')
