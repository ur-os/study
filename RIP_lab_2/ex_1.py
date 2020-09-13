#!/usr/bin/env python3
from librip.gens import field, gen_random

goods = [
    {'title': 'Ковер', 'price': 2000, 'color': 'green'},
    {'title': 'Диван для отдыха', 'price': 5300, 'color': None},
    {'title': 'Стелаж', 'price': 7000, 'color': 'Purple'},
    {'title': 'Вешалка для одежды', 'price': 800, 'color': 'white'}
]

lab1_1 = field(goods, 'title', 'color')
lab1_2 = gen_random(1, 3, 5)
print(lab1_1, lab1_2, end=' ')
