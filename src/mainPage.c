#include "mainPage.h"
#include <stddef.h>
#include <stdlib.h>

void readMainMemory(struct MainPage *mainPage, unsigned long int offset,
                    unsigned short int setSecondChance,
                    unsigned long int *readSecondaryCount) {

  if (!mainPage->valid) {

    // Page fault: fetch from secondary memory...

    (*readSecondaryCount)++;

    mainPage->valid = 1;
  }

  // Read main addr

  setSecondChance ? setAccessRecordSecondChance(mainPage->accessRecord) : NULL;
}

void writeMainMemory(struct MainPage *mainPage, unsigned long int offset,
                     unsigned short int setSecondChance,
                     unsigned long int *readSecondaryCount) {

  if (!mainPage->valid) {

    // Page fault: fetch from secondary memory...

    (*readSecondaryCount)++;

    mainPage->valid = 1;
  }

  // Write to main addr...

  mainPage->dirty = 1;
  setSecondChance ? setAccessRecordSecondChance(mainPage->accessRecord) : NULL;
}

void removeMainPage(struct MainPage *mainPage,
                    unsigned long int *writeSecondaryCount) {

  if (mainPage->valid && mainPage->dirty) {

    // Update page in secondary memory...

    (*writeSecondaryCount)++;
  }

  mainPage->valid = 0;
  mainPage->dirty = 0;
  unsetAccessRecordSecondChance(mainPage->accessRecord);
}

void replaceMainPage(struct MainPage *mainPage, unsigned long int invertedIndex,
                     unsigned long int *writeSecondaryCount) {

  removeMainPage(mainPage, writeSecondaryCount);

  mainPage->invertedIndex = invertedIndex;
}

struct AccessRecord *getMainPageAccessRecord(struct MainPage *mainPage) {
  return mainPage->accessRecord;
}

unsigned long int getMainPageInvertedIndex(struct MainPage *mainPage) {
  return mainPage->invertedIndex;
}

unsigned long int getMainPageIndex(struct MainPage *mainPage) {
  return mainPage->index;
}

struct MainPage MainPage(unsigned long int addr, unsigned long int index,
                         unsigned long int invertedIndex) {

  struct MainPage mainPage;

  mainPage.addr = addr;
  mainPage.accessRecord = malloc(sizeof(struct AccessRecord));
  *mainPage.accessRecord = AccessRecord(index);
  mainPage.index = index;
  mainPage.invertedIndex = invertedIndex;
  mainPage.valid = 0;
  mainPage.dirty = 0;

  return mainPage;
}