#include "index.h"
#include <stddef.h>
#include <stdio.h>

struct PageTable *runVirutalMemorySimulator(int argc, char **argv) {
  struct ArgParser argParser = ArgParser(argc, argv);

  FILE *inputFile = fopen(argParser.inputFilePath, "r");

  errorAssert(inputFile != NULL, "Invalid input file.");

  unsigned long int *mainAddr =
      malloc(argParser.mainMemoryKB * 1024 * sizeof(unsigned long int));

  for (int i = 0; i < argParser.mainMemoryKB * 1024; i++) {
    mainAddr[i] = i;
  }

  struct PageTable *pageTable = malloc(sizeof(struct PageTable));
  *pageTable = PageTable(VIRTUAL_MEMORY_KB, argParser.mainMemoryKB,
                         argParser.pageKB, argParser.replacementAlg, mainAddr);

  unsigned long int virtualAddr;
  char mode;

  while (fscanf(inputFile, "%lx %c", &virtualAddr, &mode) != EOF) {
    accessMemory(pageTable, virtualAddr, mode);
  }

  fclose(inputFile);

  return pageTable;
}