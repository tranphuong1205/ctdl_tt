#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int timx(int a[],int n,int x)// co gia tri x trong mang a do dai n hay ko
{
    int i;
    if(n==0)return 0;
    for(i=0;i<n;++i)
        if(a[i]==x)return 1;
    return 0;
}
void gen_random(int a[],int n)// tao n gia tri ngau nhien luu vao mang a
{
    int i,x;
    x=rand();
    for(i=0;i<n;++i)
    {
        while(timx(a,i,x))
            x=rand(); // tao ngau nhien tu 0->99
        a[i]=x;
    }
}
void swap(int *a, int *b)
 { int c = *a;
  *a = *b;
   *b = c;
 }
 void selectionsort(int *input, int size) {
     for(int i=size; i>1; i--) // cuoi day la i-1 
     { int vtMax = 0; 
     for(int j=1; j<i; j++) 
     if(input[j]>input[vtMax]) vtMax=j; 
     swap(&input[vtMax], &input[i-1]);
      } 
}
void tomtat(int n, int a[]) {
  int i;
  for (i = 0; i < n; i++) {
    int j = i;
    while (j < n - 1 && a[j + 1] == a[j] + 1) {
      j++;
    }
    if (j > i) {
      printf("%d-%d\n ", a[i], a[j]);
      i = j;
    } else {
      printf("%d\n ", a[i]);
    }
  }
}
int main()
{
    int a[10000],n,i;
    scanf("%d",&n);
    //gen_random(a,n);
    for(i=0;i<n;i++){
      scanf("%d",&a[i]);
    }
    selectionsort(a,n);
    tomtat(n,a);
    
}

