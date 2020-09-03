import numpy as np

def generateList():
    """
    Get the length from user and generate a random array of that size
    """
    upperBound = int(input("-> Please choose the Upper Bound of the array: "))
    size = int(input("-> Please choose the size of the array: "))

    return upperBound, size, np.random.randint(0, upperBound, size)

