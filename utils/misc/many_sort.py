# Many sort algorithm functions.
# For learning & references.

from math import inf
from random import choice

# Alias
array = list[int]

# NOTE: `arr` is a lvalue.

def bubble_sort(arr: array) -> array:
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr

def select_sort(arr: array) -> array:
    n = len(arr)
    
    def find_minimum(start_idx):
        """Find the minimum element, returns the INDEX."""
        nonlocal arr
        mini = inf
        mini_idx = 0
        for idx, num in enumerate(arr[start_idx:]):
            if num < mini: 
                mini = num
                mini_idx = idx
        return start_idx + mini_idx

    for i in range(n - 1):
        idx = find_minimum(i)
        arr[i], arr[idx] = arr[idx], arr[i]
    return arr

def quick_sort(arr: array) -> array: 
    n = len(arr)
    if n == 1: return arr
    pivot = choice(arr)

    left   = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right  = [x for x in arr if x > pivot]

    return quick_sort(left) + middle + quick_sort(right)

def merge_sort(arr: array) -> array:
    n = len(arr)
    if n == 1: return arr
    
    mid = n // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])

    result = []
    i = j = 0 
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result += left[i:]
    result += right[j:]

    return result
