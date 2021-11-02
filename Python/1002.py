#터렛, 기하학
from math import sqrt, pow


def distance(x1, y1, x2, y2):
    a = x1 - x2
    b = y1 - y2
    return sqrt(pow(a, 2) + pow(b, 2))


case = int(input())
for i in range(case):
    x1, y1, r1, x2, y2, r2 = map(int, input().split())
    d = distance(x1, y1, x2, y2)
    if d == 0:
        if r1 == r2:
            print(-1)
        else:
            print(0)
    else:
        if d == (r1 + r2) or d == abs(r1 - r2):
            print(1)
        elif d > (r1 + r2) or d < abs(r1 - r2):
            print(0)
        else:
            print(2)
