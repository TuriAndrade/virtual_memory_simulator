#ifndef TEST_C
#define TEST_C

#include "index.h"
#include <stddef.h>
#include <stdio.h>

#ifndef VIRTUAL_MEMORY_KB
// 2^22 KB
#define VIRTUAL_MEMORY_KB 4194304
#endif

int main(int argc, char **argv) {
  errorAssert(argc == 3, "Arg count must be equal to 3.");

  char *inputFilePath = argv[1];
  char *outputFilePath = argv[2];

  FILE *inputFile = fopen(inputFilePath, "r+");
  FILE *outputFile = fopen(outputFilePath, "w+");

  errorAssert(inputFile != NULL, "Invalid input file.");
  errorAssert(outputFile != NULL, "Invalid output file.");

  fprintf(outputFile, "%s,%s,%s,%s,%s,%s,%s\n", "input_path",
          "virtual_memory_size", "main_memory_size", "page_size",
          "replacement_algorithm", "secondary_memory_reads",
          "secondary_memory_writes");

  char replacementAlg[100];
  char inputPath[100];
  char pageKB[100];
  char mainMemoryKB[100];

  while (fscanf(inputFile, "%s %s %s %s", &replacementAlg[0], &inputPath[0],
                &pageKB[0], &mainMemoryKB[0]) != EOF) {

    int mainArgc = 5;
    char **mainArgv = malloc(5 * sizeof(char *));

    mainArgv[0] = "test";
    mainArgv[1] = replacementAlg;
    mainArgv[2] = inputPath;
    mainArgv[3] = pageKB;
    mainArgv[4] = mainMemoryKB;

    struct PageTable *pageTable = runVirutalMemorySimulator(mainArgc, mainArgv);

    fprintf(outputFile, "%s,%ld,%ld,%ld,%s,%ld,%ld\n", inputPath,
            (unsigned long int)VIRTUAL_MEMORY_KB,
            pageTable->mainMemorySize / 1024, pageTable->pageSize / 1024,
            pageTable->replacementAlg, pageTable->readSecondaryCount,
            pageTable->writeSecondaryCount);

    free(mainArgv);
    destroyPageTable(pageTable);
    free(pageTable);
  }

  fclose(inputFile);
}

#endif