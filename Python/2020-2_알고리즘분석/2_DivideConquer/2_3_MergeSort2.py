def mergeSort2(S, low, high):
    mid = (low + high) // 2

    if low < high:
        mergeSort2(S, low, mid)         #divide
        mergeSort2(S, mid + 1, high)    #divide
        merge2(S, low, mid, high)       #combine

def merge2(S, low, mid, high):
    i = low
    j = mid + 1
    U = []

    while i <= mid and j <= high:
        if S[i] < S[j]:
            U.append(S[i])
            i += 1
        else:
            U.append(S[j])
            j += 1
    if i > mid:
        U.extend(S[j:high+1])
    else:
        U.extend(S[i:mid+1])

    # 합병을 위해 임시로 만든 배열 U를 기존 배열 S로 복사
    S[low:high+1] = U[:]
    # 순간 갖고 있는 임시 배열 U의 최대 크기를 저장
    global max_memory2
    max_memory2 = max(max_memory2, len(U)) 

S = [3,5,2,9,10,14,4,8]
max_memory2 = 0
mergeSort2(S,0,7)
print(S) 
print("Additional Memory : ", max_memory2)