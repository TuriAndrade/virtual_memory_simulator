#ifndef ACCESSQUEUE_H
#define ACCESSQUEUE_H

#include "accessRecord.h"

struct AccessQueue {
  struct AccessRecord *first;
  struct AccessRecord *last;
  struct AccessRecord *current;
  unsigned long int size;
  unsigned short int updateOnAccess;
  unsigned short int clock;
};

struct AccessQueue AccessQueue(unsigned short int updateOnAccess,
                               unsigned short int clock);

void addToAccessQueue(struct AccessQueue *accessQueue,
                      struct AccessRecord *accessRecord);

struct AccessRecord *popFromAccessQueue(struct AccessQueue *accessQueue);

void destroyAccessQueue(struct AccessQueue *accessQueue);

#endif