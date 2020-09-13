#!/usr/bin/env python3
import json
import sys

from librip.ctxmngrs import timer
from librip.decorators import print_result
from librip.gens import field, gen_random
from librip.iterators import Unique as unique

path = sys.argv[1]
print(path)
with open(path) as f:
    data = json.load(f)



@print_result
def f1(arg):
    return sorted([j for j in unique((dict(i)['job-name'] for i in arg))])


@print_result
def f2(arg):
    return [*filter(lambda s: str(s).find('программист') != -1, arg)]


@print_result
def f3(arg):
    return [*map(lambda x: x + ' с опытом работы Python', arg)]


@print_result
def f4(arg):
    return [*zip(arg, [', зарплата ' for i in range(len(arg))], gen_random(100000, 200000, len(arg)))]


with timer():
    f4(f3(f2(f1(data))))
