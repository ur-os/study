import random


def field(items, *args):
    assert len(args) > 0
    b = []
    if len(args) == 1:
        for element_dict in items:
            if element_dict[args[0]] is not None:
                b.append(element_dict[args[0]])
    else:
        c = {}
        for element_dict in items:
            c.clear()
            for key in args:
                if element_dict[key] is not None:
                    c[key] = element_dict[key]
            b.append({c})
    return [b]


def gen_random(begin, end, num_count):
    return [random.randint(begin, end) for number in range(0, num_count)]
