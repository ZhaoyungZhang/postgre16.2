#include <stdio.h>     
#include <stdlib.h>     

int values[] = {40, 10, 100, 90, 20, 25, 30};

int compare (const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}

int main ()
{
  int n;
  qsort (values, sizeof(values)/sizeof(values[0]), sizeof(int), compare);
  for (n=0; n<sizeof(values)/sizeof(values[0]); n++)
     printf ("%d ",values[n]);
  return 0;
}