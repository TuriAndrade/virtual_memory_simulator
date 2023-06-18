#include "pageTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef RAND_SEED
#define RAND_SEED 42
#endif

struct PageTable PageTable(unsigned long int virtualMemoryKB,
                           unsigned long int mainMemoryKB,
                           unsigned long int pageKB, char *replacementAlg,
                           unsigned long int *mainAddr) {

  struct PageTable pageTable;

  pageTable.virtualMemorySize = virtualMemoryKB * 1024;
  pageTable.mainMemorySize = mainMemoryKB * 1024;
  pageTable.pageSize = pageKB * 1024;
  pageTable.replacementAlg = replacementAlg;
  pageTable.mainAddr = mainAddr;

  pageTable.nVirtualPages = pageTable.virtualMemorySize / pageTable.pageSize;
  pageTable.nMainPages = pageTable.mainMemorySize / pageTable.pageSize;
  pageTable.currentMainPage = 0;
  pageTable.readSecondaryCount = 0;
  pageTable.writeSecondaryCount = 0;
  pageTable.mainPages = malloc(pageTable.nMainPages * sizeof(struct MainPage));
  pageTable.virtualPages =
      malloc(pageTable.nVirtualPages * sizeof(unsigned long int));
  pageTable.accessQueue = NULL;

  if (strcmp(pageTable.replacementAlg, "random") != 0) {
    pageTable.accessQueue = malloc(sizeof(struct AccessQueue));

    *(pageTable.accessQueue) =
        AccessQueue(strcmp(pageTable.replacementAlg, "lru") == 0 ? 1 : 0,
                    strcmp(pageTable.replacementAlg, "2a") == 0 ? 1 : 0);
  }

  for (int i = 0; i <= pageTable.nVirtualPages; i++) {
    pageTable.virtualPages[i] = pageTable.nMainPages;
  }

  srand(RAND_SEED);

  return pageTable;
}

unsigned long int accessBasedReplacement(struct PageTable *pageTable) {
  struct AccessRecord *accessRecord =
      popFromAccessQueue(pageTable->accessQueue);

  unsigned long int pageIndexToReplace =
      getAccessRecordMainPageIndex(accessRecord);

  return pageIndexToReplace;
}

unsigned long int randomReplacement(struct PageTable *pageTable) {
  unsigned long int pageIndexToReplace = rand() % pageTable->nMainPages;

  return pageIndexToReplace;
}

unsigned long int selectPageToReplace(struct PageTable *pageTable) {

  if (strcmp(pageTable->replacementAlg, "lru") == 0 ||
      strcmp(pageTable->replacementAlg, "fifo") == 0 ||
      strcmp(pageTable->replacementAlg, "2a") == 0) {

    return accessBasedReplacement(pageTable);

  } else if (strcmp(pageTable->replacementAlg, "random") == 0) {

    return randomReplacement(pageTable);
  } else {

    return pageTable->nMainPages;
  }
}

void updatePageTableAccessQueue(struct PageTable *pageTable,
                                struct AccessQueue *accessQueue,
                                struct AccessRecord *accessRecord) {
  if (pageTable->accessQueue != NULL) {

    addToAccessQueue(accessQueue, accessRecord);
  }
}

void accessMemory(struct PageTable *pageTable, unsigned long int virtualAddr,
                  char mode) {
  unsigned long int virtualPageIndex = virtualAddr / pageTable->pageSize;
  unsigned long int pageOffset = virtualAddr % pageTable->pageSize;

  if (pageTable->virtualPages[virtualPageIndex] == pageTable->nMainPages) {

    if (pageTable->currentMainPage < pageTable->nMainPages) {

      pageTable->mainPages[pageTable->currentMainPage] =
          MainPage(pageTable->mainAddr[pageTable->currentMainPage],
                   pageTable->currentMainPage, virtualPageIndex);

      if (mode == 'R') {

        readMainMemory(&pageTable->mainPages[pageTable->currentMainPage],
                       pageOffset, 0, &pageTable->readSecondaryCount);

      } else if (mode == 'W') {

        writeMainMemory(&pageTable->mainPages[pageTable->currentMainPage],
                        pageOffset, 0, &pageTable->readSecondaryCount);
      }

      LOGMEMORYACCESS(virtualAddr, pageTable->currentMainPage, pageOffset,
                      mode);

      updatePageTableAccessQueue(
          pageTable, pageTable->accessQueue,
          getMainPageAccessRecord(
              &pageTable->mainPages[pageTable->currentMainPage]));

      pageTable->virtualPages[virtualPageIndex] = pageTable->currentMainPage;
      pageTable->currentMainPage++;

    } else {

      struct MainPage *pageToReplace =
          &pageTable->mainPages[selectPageToReplace(pageTable)];

      pageTable->virtualPages[getMainPageInvertedIndex(pageToReplace)] =
          pageTable->nMainPages;

      pageTable->virtualPages[virtualPageIndex] =
          getMainPageIndex(pageToReplace);

      replaceMainPage(pageToReplace, virtualPageIndex,
                      &pageTable->writeSecondaryCount);

      if (mode == 'R') {

        readMainMemory(pageToReplace, pageOffset, 0,
                       &pageTable->readSecondaryCount);

      } else if (mode == 'W') {

        writeMainMemory(pageToReplace, pageOffset, 0,
                        &pageTable->readSecondaryCount);
      }

      LOGMEMORYACCESS(virtualAddr, getMainPageIndex(pageToReplace), pageOffset,
                      mode);

      updatePageTableAccessQueue(pageTable, pageTable->accessQueue,
                                 getMainPageAccessRecord(pageToReplace));
    }

  } else {

    if (mode == 'R') {

      readMainMemory(
          &pageTable->mainPages[pageTable->virtualPages[virtualPageIndex]],
          pageOffset, 1, &pageTable->readSecondaryCount);

    } else if (mode == 'W') {

      writeMainMemory(
          &pageTable->mainPages[pageTable->virtualPages[virtualPageIndex]],
          pageOffset, 1, &pageTable->readSecondaryCount);
    }

    LOGMEMORYACCESS(virtualAddr, pageTable->virtualPages[virtualPageIndex],
                    pageOffset, mode);

    updatePageTableAccessQueue(
        pageTable, pageTable->accessQueue,
        getMainPageAccessRecord(
            &pageTable->mainPages[pageTable->virtualPages[virtualPageIndex]]));
  }
}

void logMemoryAccess(unsigned long int virtualAddr,
                     unsigned long int virtualPage, unsigned long int offset,
                     char mode) {
  printf("Memory Access: %lx %ld %ld %c\n", virtualAddr, virtualPage, offset,
         mode);
}

char *reportPageTable(struct PageTable *pageTable) {
  char *report = malloc(500 * sizeof(char));

  sprintf(report,
          "-------------- PAGE TABLE REPORT --------------\nVirtual "
          "memory size: %ld KB\nMain memory size: %ld KB\nPage size: "
          "%ld KB\nPage replacement algorithm: %s\nNumber of secondary memory "
          "reads: %ld\nNumber of secondary memory writes: %ld\n",
          pageTable->virtualMemorySize / 1024, pageTable->mainMemorySize / 1024,
          pageTable->pageSize / 1024, pageTable->replacementAlg,
          pageTable->readSecondaryCount, pageTable->writeSecondaryCount);

  return report;
}

void destroyPageTable(struct PageTable *pageTable) {

  free(pageTable->mainAddr);
  free(pageTable->virtualPages);
  free(pageTable->mainPages);

  if (pageTable->accessQueue != NULL) {
    destroyAccessQueue(pageTable->accessQueue);

    free(pageTable->accessQueue);
  }
}