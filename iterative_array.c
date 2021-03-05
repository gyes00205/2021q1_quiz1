#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>  

bool quickSort(int *arr, int elements) {
    #define MAX_LEVELS  1000

    int piv, beg[MAX_LEVELS], end[MAX_LEVELS], i=0, L, R ;

    beg[0]=0; end[0]=elements;
    while (i>=0) {
        // printf("i = %d\nbeg[i] = %d, end[i] = %d\n", i, beg[i], end[i]);
        L=beg[i]; R=end[i]-1;
        if (L<R) {
            piv=arr[L];
            if (i==MAX_LEVELS-1) 
                return false;
            while (L<R) {
                while (arr[R]>=piv && L<R) 
                    R--; 
                if (L<R) 
                    arr[L++]=arr[R];
                while (arr[L]<=piv && L<R) 
                    L++; 
                if (L<R) 
                    arr[R--]=arr[L];
            }
            arr[L]=piv; beg[i+1]=L+1; end[i+1]=end[i]; end[i++]=L; 
            // printf("beg[i] = %d, end[i] = %d\n", beg[i-1], end[i-1]);
        }
        else
            i--;
    }
    return true; 
}

int main(int argc, char **argv)
{
    printf("argc: %d\n", argc);
    int arr[argc-1];
    for (int i=0;i<argc-1;i++){
        arr[i] = atoi(argv[i+1]);
        
    }
    bool result = quickSort(arr, argc-1);
    for(int i=0;i<argc-1;i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}