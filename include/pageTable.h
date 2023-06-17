#ifndef PAGETABLE_H
#define PAGETABLE_H

#ifdef VERBOSE
#define LOGMEMORYACCESS(virtualAddr, virtualPage, offset, mode)                \
  (void)logMemoryAccess(virtualAddr, virtualPage, offset, mode)

#else
#define LOGMEMORYACCESS(virtualAddr, virtualPage, offset, mode) (void)NULL

#endif

#include "accessQueue.h"
#include "mainPage.h"

struct PageTable {
  unsigned long int virtualMemorySize;
  unsigned long int mainMemorySize;
  unsigned long int pageSize;
  unsigned long int nVirtualPages;
  unsigned long int nMainPages;
  unsigned long int currentMainPage;
  unsigned long int *mainAddr;
  unsigned long int *virtualPages;
  unsigned long int readSecondaryCount;
  unsigned long int writeSecondaryCount;
  struct MainPage *mainPages;
  struct AccessQueue *accessQueue;
  char *replacementAlg;
};

struct PageTable PageTable(unsigned long int virtualMemoryKB,
                           unsigned long int mainMemoryKB,
                           unsigned long int pageKB, char *replacementAlg,
                           unsigned long int *mainAddr);

void accessMemory(struct PageTable *pageTable, unsigned long int virtualAddr,
                  char mode);

void logMemoryAccess(unsigned long int virtualAddr,
                     unsigned long int virtualPage, unsigned long int offset,
                     char mode);

void reportPageTable(struct PageTable *pageTable);

unsigned long int runReplacementAlgorithm(struct PageTable *pageTable);

unsigned long int randomReplacement(struct PageTable *pageTable);

unsigned long int accessBasedReplacement(struct PageTable *pageTable);

void updatePageTableAccessQueue(struct PageTable *pageTable,
                                struct AccessQueue *accessQueue,
                                struct AccessRecord *accessRecord);

void destroyPageTable(struct PageTable *pageTable);

#endif