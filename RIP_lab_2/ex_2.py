#!/usr/bin/env python3
from librip.gens import gen_random
from librip.iterators import Unique

data1 = [1, 1, 1, "a", "A", 2, 2, 2, 2, 2]
data2 = gen_random(1, 3, 10)

print(data1)
itera = Unique(data1, ignore_case=False)

for i in itera:
    print(i, end=" ")
print()
print(data2)
itera = Unique(data2, ignore_case=False)

for i in itera:
    print(i, end=" ")