#ifndef MAIN_C
#define MAIN_C

#include "argParser.h"
#include "assert.h"
#include "pageTable.h"
#include <stddef.h>
#include <stdio.h>

#ifndef VIRTUAL_MEMORY_KB
// 2^22 KB
#define VIRTUAL_MEMORY_KB 4194304
#endif

int main(int argc, char **argv) {
  struct ArgParser argParser = ArgParser(argc, argv);

  FILE *inputFile = fopen(argParser.inputFilePath, "r");

  errorAssert(inputFile != NULL, "Invalid input file.");

  unsigned long int *mainAddr =
      malloc(argParser.mainMemoryKB * 1024 * sizeof(unsigned long int));

  for (int i = 0; i < argParser.mainMemoryKB * 1024; i++) {
    mainAddr[i] = i;
  }

  struct PageTable pageTable =
      PageTable(VIRTUAL_MEMORY_KB, argParser.mainMemoryKB, argParser.pageKB,
                argParser.replacementAlg, mainAddr);

  unsigned long int virtualAddr;
  char mode;

  while (fscanf(inputFile, "%lx %c", &virtualAddr, &mode) != EOF) {
    accessMemory(&pageTable, virtualAddr, mode);
  }

  reportPageTable(&pageTable);

  destroyPageTable(&pageTable);
}

#endif