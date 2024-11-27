#include <stdio.h>
#include <omp.h>

int main(){
    int i;
    int N =10;
    int x = 0;
    int a[N];
    int b[N];
    int c[N];

    for (i = 0; i<N+1;i++){
        a[i] = b[i] = c[i] = i;
    }

    int ccopy[N];
    int xvector[N];
    for (i =0;i<N;i++){
        x = x + a[i];
        xvector[i] = x;
    }
    
    #pragma omp parallel for
    for (i =0;i<N+1;i++){
        ccopy[i] = c[i];
        
    }

    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        b[i] = b[i] * xvector[i];
        c[i] = ccopy[i + 1] + b[i];
    }

    printf("%d\n",x);

    for (i = 0; i<N;i++){
        printf("%d ",a[i]);
    }
    printf("\n");

    for (i = 0; i<N;i++){
        printf("%d ",b[i]);
    }
    printf("\n");

    for (i = 0; i<N;i++){
        printf("%d ",c[i]);
    }
    printf("\n");
}

/*
45
0 1 2 3 4 5 6 7 8 9 
0 1 6 18 40 75 126 196 288 405 
1 3 9 22 45 81 133 204 297 699258980 
*/