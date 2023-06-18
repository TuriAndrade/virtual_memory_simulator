#include "index.h"
#include <stddef.h>
#include <stdio.h>

int main(int argc, char **argv) {
  struct PageTable *pageTable = runVirutalMemorySimulator(argc, argv);

  char *report = reportPageTable(pageTable);

  printf("%s", report);

  free(report);
  destroyPageTable(pageTable);
  free(pageTable);

  return 0;
}