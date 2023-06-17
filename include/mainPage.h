#ifndef MAINPAGE_H
#define MAINPAGE_H

#include "accessRecord.h"

struct MainPage {
  unsigned long int addr;
  struct AccessRecord *accessRecord;
  unsigned long int index;
  unsigned long int invertedIndex;
  unsigned short int valid;
  unsigned short int dirty;
};

void readMainMemory(struct MainPage *mainPage, unsigned long int offset,
                    unsigned short int setSecondChance,
                    unsigned long int *readSecondaryCount);

void writeMainMemory(struct MainPage *mainPage, unsigned long int offset,
                     unsigned short int setSecondChance,
                     unsigned long int *readSecondaryCount);

void removeMainPage(struct MainPage *mainPage,
                    unsigned long int *writeSecondaryCount);

void replaceMainPage(struct MainPage *mainPage, unsigned long int invertedIndex,
                     unsigned long int *writeSecondaryCount);

unsigned long int getMainPageInvertedIndex(struct MainPage *mainPage);

unsigned long int getMainPageIndex(struct MainPage *mainPage);

struct MainPage MainPage(unsigned long int addr, unsigned long int index,
                         unsigned long int invertedIndex);

struct AccessRecord *getMainPageAccessRecord(struct MainPage *mainPage);

void destroyMainPage(struct MainPage *mainPage);

#endif