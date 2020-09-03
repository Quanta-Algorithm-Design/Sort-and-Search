#!/usr/bin/env python3

# I'll be trying to implement the counting sort in this file...
########################################
###### Author: Alpha Leo ###############
########################################

# This data structure assumes that listA is a list of Integers
# of size n between 0 and k-1
# Then it creates pos which first, counts the occurence of each
# int from 0 to k-1, and then uses an algorithm to find the number
# of items -LE to the item of the index. Then it uses that information
# to sort the whole thing in linear time.
# This is a practice of "Stable Sorting" which will come in handy for Radix Sort

from generator import generateList

def countSort(k, n, arrA):
    # Initialize a list of size 200 with values 0. This is the count.
    pos = [0] * k

    # Count the occurence of each int.
    for item in arrA:
        pos[item] += 1

    # Find the number of items -LE the item and store it instead of count.
    for i in range(1, upBound):
        pos[i] += pos[i-1]

    out = [0] * n

    # Find the position of each item from pos map it in out
    for index in range(n-1, -1, -1):
        pos[arrA[index]] -= 1
        out[pos[arrA[index]]] = arrA[index]

    return out


def main():
    inList = []
    up, size, arr = generateList()
    for item in arr:
        inList.append(item)

    print(countSort(up, size, inList))
    return 0

# Profiler to benchmark the output for performance test.
if __name__ == "__main__":
    import cProfile
    cProfile.run("main()")
