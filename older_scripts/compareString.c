#include<stdio.h>
#include<stdlib.h>

void main(int argc, char* argv[]) {
  if(argc > 3) {
    printf("Too many arguments. Terminating.\n");
    return;
  }
  const char * file1 = argv[1];
  const char * file2 = argv[2];
  const char * mode  = "r";

  FILE * f1;
  FILE * f2;

  f1 = fopen(file1, mode);
  f2 = fopen(file2, mode);

  char comp1[1999];
  char comp2[1999];

  fgets(comp1, 1999, f1);
  fgets(comp2, 1999, f2);

  int i = 0;
  int j = 2;
  for(i = 0; i < 1999; i++) {
    if(comp1[i] != comp2[i]) {
      printf("Failed at %d\n", i);
    }
    if(j == i) {
      if(comp2[i] >='6') {
	printf("Ignored %d: Too far away\n", i);
      }
      j += 20;
    } 
  }
  printf("Comparison Complete\n\n");

  fclose(f1);
  fclose(f2);

  return;
}
