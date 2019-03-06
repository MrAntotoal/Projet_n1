#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  printf("%s\n",argv[1]);

  printf("%c\n",argv[1][strlen(argv[1]) + 2]);
  return 0;
}
