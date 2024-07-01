#!/bin/env python3

import numpy as np

def f(x: float):
    return np.exp(x)-x

def main():
    a = 0
    b = 2
    mp1 = 41
    for i in range(0, mp1):
        x = a + (b-a) * i / (mp1 - 1)
        print(f"{x}\t{f(x)}")

if __name__ == "__main__":
   main() 
