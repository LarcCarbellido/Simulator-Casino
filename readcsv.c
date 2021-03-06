#include <stdio.h>
#include <stdlib.h>
 
#define FIRST_LINE   500
#define LAST_LINE   1000
 
int main() {
  char buf[1024];
  int line_count = 0;
  FILE *file = fopen("settings.csv", "r");
 
  if (!file) {
    fprintf(stderr, "Can't open file.\n");
    exit(EXIT_FAILURE);
  }
 
  while (fgets(buf, sizeof buf, file) != NULL)
    if (++line_count >= FIRST_LINE - 1)
      break;
 
  while (fgets(buf, sizeof buf, file) != NULL) {
    double value;
 
    // read value in third column (asterisk means ignore value)
    if (sscanf(buf, "%*lf,%*lf,%lf", &value) != 1) {
      fprintf(stderr, "sscanf failed.\n");
      exit(EXIT_FAILURE);
    }
 
    printf("%f\n", value);
    if (++line_count >= 1000)
      break;
  }
 
  fclose(file);
  return 0;
}