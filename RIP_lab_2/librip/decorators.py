def print_result(function_to_decorate):
    def wrapper(data=None):
        print(function_to_decorate.__name__)
        if data is None:
            foo_result = function_to_decorate()
        else:
            foo_result = function_to_decorate(data)

        if type(foo_result) is list:
            for node in foo_result:
                print(node)

        elif type(foo_result) is dict:
            for key in foo_result:
                print(key, ':', foo_result[key])


        else:
            print(foo_result)
        if data is None:
            return function_to_decorate()
        else:
            return function_to_decorate(data)

    return wrapper
