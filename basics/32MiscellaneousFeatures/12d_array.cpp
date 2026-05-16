#include "12c_array.h"
#include <stdio.h>

int array_print(int arr[], int n) {
  int i = 0;
  for (i = 0; i < n; ++i) {
    printf("%d", arr[i]);
  }
  printf("\n");
}
