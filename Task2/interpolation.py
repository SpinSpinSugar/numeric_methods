#!/bin/env python3

import numpy as np
import scipy as sp

def f(x: float) -> float:
    return np.exp(x)-x


def main():
    print("Interpolation")
    print("Var XX")
    mp1: int = int(input("Table size:"))
    a: float = float(input("a:"))
    b: float = float(input("b:"))
    x: float = float(input("x:"))
    n: int = int(input("Polynom degree"))
    assert n <= mp1 - 1, "Incorrect n value"

    table: list[(float, float)] = []
    for i in range(0, mp1):
        table.append(tuple(map(float, input().split())))
    table.sort(key = lambda rhs: abs(rhs[1] - x))
    """
    if __debug__:
        print(table)
        print("______SORTED______")
        print(table)
    """
    xtbl = [x for x in list(map(lambda t: t[0], table[:n]))]
    #print(xtbl)
    xtable = np.array(xtbl)
    ytbl = [y for y in list(map(lambda t: t[1], table[:n]))]
    #print(ytbl)
    ytable = np.array(ytbl)
    poly = sp.interpolate.lagrange(xtable, ytable)
    #print(poly.coef)
    print(f"x={x}")
    print("Lagrange Interpolation")
    print(f"f(x)={poly(x)}")
    print(f"err={abs(f(x) - poly(x)})")

if __name__ == "__main__":
    main()
