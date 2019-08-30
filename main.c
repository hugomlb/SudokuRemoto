#include "RuleVerifier.h"
#include <stdio.h>

#define C 3

int main(int argc, char const *argv[]) {
  int a[3] [3];
  int ind = 1;
  for (int i = 0; i < 3; i ++) {
    for (int j = 0; j < 3; j ++) {
      a[i][j] = ind;
      ind ++;
    }
  }
  int *p = & a[0][0];
  printf("%d\n", *(p+(C*0)));
  printf("%d\n", *(p+(C*1)));
  printf("%d\n", *(p+(C*2)));
  return 0;
}
