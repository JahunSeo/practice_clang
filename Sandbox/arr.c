#include <stdio.h>
int main() {
  int b = 3;
  const int a = 5;
  char c[a] = {1,2};
  printf("%d \n", c[0]);
  return 0;
}