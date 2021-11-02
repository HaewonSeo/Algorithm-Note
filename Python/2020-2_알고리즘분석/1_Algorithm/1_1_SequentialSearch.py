def seqsearch(s, x):
    n = len(s)
    for i in range(n):
        if s[i] == x:
            return (i)
    return (0)

s = [3,5,2,1,7,9]
loc = seqsearch(s,5)
print(loc)