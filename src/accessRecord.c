#include "accessRecord.h"
#include <stddef.h>
#include <stdlib.h>

struct AccessRecord AccessRecord(unsigned long int mainPageIndex) {

  struct AccessRecord accessRecord;

  accessRecord.mainPageIndex = mainPageIndex;
  accessRecord.isInAccessQueue = 0;
  accessRecord.secondChance = 0;
  accessRecord.prev = NULL;
  accessRecord.next = NULL;

  return accessRecord;
}

void setPrevAccessRecord(struct AccessRecord *current,
                         struct AccessRecord *prev) {

  if (current != NULL) {
    current->prev = prev;
  }
}

void setNextAccessRecord(struct AccessRecord *current,
                         struct AccessRecord *next) {
  if (current != NULL) {
    current->next = next;
  }
}

short int isInAccessQueue(struct AccessRecord *accessRecord) {

  return accessRecord->isInAccessQueue;
}

void setIsInAccessQueue(struct AccessRecord *accessRecord) {
  accessRecord->isInAccessQueue = 1;
}

void unsetIsInAccessQueue(struct AccessRecord *accessRecord) {
  accessRecord->isInAccessQueue = 0;
}

void setAccessRecordSecondChance(struct AccessRecord *accessRecord) {
  accessRecord->secondChance = 1;
}

void unsetAccessRecordSecondChance(struct AccessRecord *accessRecord) {
  accessRecord->secondChance = 0;
}

unsigned short int
getAccessRecordSecondChance(struct AccessRecord *accessRecord) {
  return accessRecord->secondChance;
}

struct AccessRecord *getPrevAccessRecord(struct AccessRecord *accessRecord) {
  return accessRecord->prev;
}

struct AccessRecord *getNextAccessRecord(struct AccessRecord *accessRecord) {
  return accessRecord->next;
}

unsigned long int
getAccessRecordMainPageIndex(struct AccessRecord *accessRecord) {
  return accessRecord->mainPageIndex;
}

void destroyAccessRecord(struct AccessRecord *accessRecord) {

  free(accessRecord);
}