from fastrand import pcg32bounded   # A C-Level random generator (costs 1/10 of randint)

def generate_list():
    """
    Get the length from user and generate a random array of that size
    """
    upper_bound = int(input("-> Please choose the Upper Bound of the array: "))
    size = int(input("-> Please choose the size of the array: "))

    # return upperBound, size, np.random.randint(0, upperBound, size)

    rand_arr = []
    for _ in range(size):
        rand_arr.append(pcg32bounded(upper_bound))

    return upper_bound, size, rand_arr
