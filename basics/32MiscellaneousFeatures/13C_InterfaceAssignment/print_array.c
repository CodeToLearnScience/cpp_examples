#include "print_array.h"
#include <stdio.h>

void print_array(int arr[], int size) {

  for (int i = 0; i < size; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}
