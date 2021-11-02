#피보나치 함수

def ft_count(n):
    length = len(zero)
    if n >= length:
        for i in range(length, n + 1):
            zero.append(zero[i-2] + zero[i-1])
            one.append(one[i-2] + one[i-1])
    print("{0} {1}".format(zero[n], one[n]))

case = int(input())
zero = [1, 0, 1]
one = [0, 1, 1]

for i in range(case):
    ft_count(int(input()))
