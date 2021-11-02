// 내림차순
void qsort(int l, int r) {
    int s=l; int e=r;
    int pivot = arr[(l+r)/2];

    if(l >= r) return;

    while(s <= e){
        while(arr[s] > pivot) s++;
        while(arr[e] < pivot) e--;
        if(s <= e){
            int temp;
            temp = arr[s];
            arr[s] = arr[e];
            arr[e] = temp;
            s++; e--;
        }
    }
    qsort(l,e);
    qsort(s,r);
}
