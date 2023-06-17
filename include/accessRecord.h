#ifndef ACCESSRECORD_H
#define ACCESSRECORD_H

struct AccessRecord {
  unsigned long int mainPageIndex;
  unsigned short int isInAccessQueue;
  unsigned short int secondChance;
  struct AccessRecord *prev;
  struct AccessRecord *next;
};

struct AccessRecord AccessRecord(unsigned long int mainPageIndex);

void setPrevAccessRecord(struct AccessRecord *current,
                         struct AccessRecord *prev);

void setNextAccessRecord(struct AccessRecord *current,
                         struct AccessRecord *next);

void setIsInAccessQueue(struct AccessRecord *accessRecord);

void unsetIsInAccessQueue(struct AccessRecord *accessRecord);

void setAccessRecordSecondChance(struct AccessRecord *accessRecord);

void unsetAccessRecordSecondChance(struct AccessRecord *accessRecord);

unsigned short int
getAccessRecordSecondChance(struct AccessRecord *accessRecord);

struct AccessRecord *getPrevAccessRecord(struct AccessRecord *accessRecord);

struct AccessRecord *getNextAccessRecord(struct AccessRecord *accessRecord);

unsigned long int
getAccessRecordMainPageIndex(struct AccessRecord *accessRecord);

short int isInAccessQueue(struct AccessRecord *accessRecord);

void destroyAccessRecord(struct AccessRecord *accessRecord);

#endif