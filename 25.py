"""
It is well known that F_n ~ phi**n / sqrt(5), 
so just set LHS to 1e1000 = 10**9999 and solve using log properties
log(10**999) = log(phi**n / sqrt(5))
n = (999 * log(10) + log(5)/2)/log(phi)
"""
from math import log, sqrt, ceil

phi = (1 + sqrt(5)) / 2
n = ceil((999 * log(10) + log(5)/2) / log(phi))
print(f'ans={n}')
