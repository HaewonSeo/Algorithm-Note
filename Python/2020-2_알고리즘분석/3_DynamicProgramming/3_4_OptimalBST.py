import utility

class Node:
    def __init__(self, data):
        self.l_child = None
        self.r_child = None
        self.data = data

def tree(key, r, i, j):
    k = r[i][j]
    if (k == 0):
        return
    else:
        p = Node(key[k])
        p.l_child = tree(key,r,i,k-1)
        p.r_child = tree(key,r,k+1,j)
        return p


key = [" ","A","B","C","D"]
p = [0, 0.3, 0.1, 0.2, 0.4]
n = len(p) - 1

# Initializing and Padding Matrix a&r (4*4 -> 6*6)
# a[i][j] : Optimal search time of tree includes KEYi to KEYj
# r[i][j] : Optimal root of tree includes KEYi to KEYj
a = [[0 for j in range(0,n+2)] for i in range(0,n+2)]
r = [[0 for j in range(0,n+2)] for i in range(0,n+2)]

# Intialize Diagonal -1&0 of Matrix a&r
for i in range (1,n+1):
    a[i][i-1] = 0
    a[i][i] = p[i]
    r[i][i] = i
    r[i][i-1] = 0
a[n+1][n] = 0
r[n+1][n] = 0

def optsearchtree(n, p, a, r):
	for diagonal in range(1, n):
		for i in range(1, n-diagonal+1):
			j = i + diagonal
			# Initialize a&r&psum
			a[i][j] = a[i][i-1] + a[i+1][j]
			r[i][j] = i
			psum = 0
			for k in range(i, j+1):
				# Sum of p[i to j]
				psum += p[k]
				if (a[i][k-1] + a[k+1][j]) < a[i][j]:
					a[i][j] = a[i][k-1] + a[k+1][j]
					r[i][j] = k
			a[i][j] += psum

optsearchtree(n, p, a, r)

utility.printMatrixF(a)
print()
utility.printMatrix(r)

root = tree(key,r,1,n)
print("\nInorder")
utility.print_inOrder(root)
print("\nPreorder")
utility.print_preOrder(root)
print("\nPostorder")
utility.print_postOrder(root)
