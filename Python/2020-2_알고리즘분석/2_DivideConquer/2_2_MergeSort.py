def mergeSort(n, S):
    h = n // 2
    m = n - h

    if n > 1:
        U = S[:h]
        V = S[h:]
        #분할 전 필요한 추가 메모리의 총합을 계산
        global memory, max_memory
        memory += len(U) + len(V)
        #합병정렬 중에 순간 추가 메모리의 최대값를 계산
        max_memory = max(memory, max_memory)
        mergeSort(h, U)                     #divide
        mergeSort(m, V)                     #divide
        merge(h,m,U,V,S)                    #combine
        #합병 후 사용한 추가 메모리는 총합에서 제외
        memory -= (len(U) + len(V))
        
def merge(h,m,U,V,S):
    i = 0; j = 0; k = 0

    while(i < h and j < m):
        if U[i] < V[j]:
            S[k] = U[i]
            i += 1
        else:
            S[k] = V[j]
            j += 1
        k += 1
    if i >= h:
        S[k:] = V[j:]
    else:
        S[k:] = U[i:]

S=[3,5,2,9,10,14,4,8]
memory = 0 ; max_memory = 0
mergeSort(8, S)
print(S)
print("Additional Memory : ", max_memory)
