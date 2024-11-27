#include <stdio.h>
#include <omp.h>

int main(){
    int i;
    int N =10;
    int x = 0;
    int y;
    int a[N];
    int b[N];
    int c[N];

    for (i = 0; i<N;i++){
        a[i] = b[i] = c[i] = i;
    }

    b[1] = b[1]+ c[0];
    #pragma omp parallel for reduction(+: x) private(y)
    for (i = 1; i < N-1; i++) {
        x = x + a[i];
        y = a[i] + i;
        c[i] = c[i] + y;
        b[i+1] = b[i+1] + c[i];
    }

    x = x + a[N-1];
    y = a[N-1] + N-1;
    c[N-1] = c[N-1] + y;

    printf("%d %d\n",x,y);

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