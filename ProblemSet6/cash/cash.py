from cs50 import get_float
import math

#quarter = 25
#dimes = 10
#nickels = 5
#pennies = 1

while True:
    dollar = get_float("Change owed: ")
    if dollar > 0:
        break
cent = dollar * 100

#quarters
q = math.floor(cent/25)

#dimes
l1 = cent - (25 * q)
d = math.floor(l1/10)

#nickels
l2 = l1 - (10 * d)
n = math.floor(l2/5)

#pennies
l3 = l2 - (5 * n)
p = math.floor(l3)

#total number of coins
t = q + d + n + p
print(f"{t}")