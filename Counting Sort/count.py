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

from generator import generate_list

def countSort(k, n, arr_a):
    # Initialize a list of size k with values 0. This is the count.
    pos = [0] * k

    # Count the occurence of each int.
    for item in arr_a:
        pos[item] += 1

    # Find the number of items -LE the item and store it instead of count.
    for i in range(1, k):
        pos[i] += pos[i-1]

    out = [0] * n

    # Find the position of each item from pos map it in out
    for index in range(n-1, -1, -1):
        pos[arr_a[index]] -= 1
        out[pos[arr_a[index]]] = arr_a[index]

    return out


def main():
    input_list = []
    up, size, arr = generate_list()
    for item in arr:
        input_list.append(item)

    print(countSort(up, size, input_list))
    return 0

# Profiler to benchmark the output for performance test.
if __name__ == "__main__":
    import cProfile
    cProfile.run("main()")
