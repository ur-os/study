class Unique(object):
    def __init__(self, items, **kwargs):
        self.items = list(items)
        self.items = [str(x) for x in self.items]
        self.unique_list = []
        self.current = 0
        self.ignore_case = False
        if len(kwargs) != 0:
            self.ignore_case = kwargs["ignore_case"]

    def __iter__(self):
        return self

    # FFFFFFFF
    # FF
    # FFFFFF
    # FF
    # FF
    # FF

    # :(

    def __next__(self):
        while True:
            if self.current >= len(self.items):
                raise StopIteration
            if self.ignore_case is False:
                if self.items[self.current].upper() and self.items[self.current].lower() not in self.unique_list:
                    self.unique_list.append(self.items[self.current].lower())
                    self.current += 1
                    return self.unique_list[len(self.unique_list) - 1]

            if self.ignore_case is True:
                if (self.items[self.current].upper() or self.items[self.current].lower()) not in self.unique_list:
                    self.unique_list.append(self.items[self.current])
                    self.current += 1
                    return self.unique_list[len(self.unique_list) - 1]

            self.current += 1
