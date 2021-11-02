import time

#Recursion
def fib1(n):
    if (n <= 1):
        return n
    else:
        return fib1(n-1) + fib1(n-2)

#Iteration
def fib2(n):
    f = [0] * (n+1)
    f[0] = 0
    if (n > 0):
        f[1] = 1
        for i in range(2, n+1):
            f[i] = f[i-1] + f[i-2]
    return f[n]

# print('fib1')
# for i in range(0,10):
#     print('%2d  %6d ' % (i,  fib1(i)))

# print('fib2')
# for i in range(0,10):
#     print('%2d  %6d ' % (i, fib2(i)))

# for i in range(30,36):
#     stime =  time.time()
#     fib1(i)
#     print( '%2d  %10.5f ' % (i, time.time() - stime ))

# for i in range(30,36):
#     stime =  time.time()
#     fib2(i)
#     print( '%2d  %10.5f ' % (i, time.time() - stime ))

n = 35
stime =  time.time()
fib1(n)
print('fib1')
print( '%2d  %10.5f ' % (n, time.time() - stime ))

stime = time.time()
fib2(n)
print('fib2')
print( '%2d  %10.5f ' % (n, time.time() - stime ))
