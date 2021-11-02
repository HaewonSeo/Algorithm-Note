def prod2(u,v):
    threshold = 4
    n = max(len(str(u)), len(str(v)))

    if u == 0 or v == 0:
        return 0
    elif n <= threshold:
        return u*v
    else:
        m = n // 2
        x, y = divmod(u, pow(10,m))
        w, z = divmod(v, pow(10,m))

        r = prod2(x+y, w+z)
        p = prod2(x, w)
        q = prod2(y, z)

        return p*pow(10,2*m) + (r-p-q)*pow(10,m) + q
    
a=1234567812345678
b=2345678923456789

print(prod2(a,b))
print(a*b)
