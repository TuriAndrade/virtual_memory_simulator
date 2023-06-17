#ifndef ARGPARSER_H
#define ARGPARSER_H

struct ArgParser {
  char *replacementAlg;
  char *inputFilePath;
  unsigned long int pageKB;
  unsigned long int mainMemoryKB;
};

struct ArgParser ArgParser(int argc, char **argv);

#endif