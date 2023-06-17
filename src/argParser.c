#include "argParser.h"
#include "assert.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct ArgParser ArgParser(int argc, char **argv) {

  errorAssert(argc == 5, "Arg count must be equal to 5.");

  struct ArgParser argParser;

  argParser.replacementAlg = argv[1];
  argParser.inputFilePath = argv[2];
  argParser.pageKB = strtoul(argv[3], NULL, 10);
  argParser.mainMemoryKB = strtoul(argv[4], NULL, 10);

  errorAssert(strcmp(argParser.replacementAlg, "lru") == 0 ||
                  strcmp(argParser.replacementAlg, "fifo") == 0 ||
                  strcmp(argParser.replacementAlg, "random") == 0 ||
                  strcmp(argParser.replacementAlg, "2a") == 0,
              "Invalid replacement algorithm.");

  errorAssert(argParser.pageKB > 0, "Page size must be greater than 0.");

  errorAssert(argParser.mainMemoryKB >= argParser.pageKB,
              "Main memory size must be greater than or equal to page size.");

  return argParser;
}