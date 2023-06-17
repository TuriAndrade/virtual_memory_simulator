#include "accessQueue.h"
#include <stddef.h>
#include <stdlib.h>

struct AccessQueue AccessQueue(unsigned short int updateOnAccess,
                               unsigned short int clock) {

  struct AccessQueue accessQueue;

  accessQueue.updateOnAccess = updateOnAccess;
  accessQueue.clock = clock;

  accessQueue.first = malloc(sizeof(struct AccessRecord));
  *(accessQueue.first) = AccessRecord(0);

  accessQueue.last = malloc(sizeof(struct AccessRecord));
  *(accessQueue.last) = AccessRecord(0);

  setNextAccessRecord(accessQueue.first, accessQueue.last);
  setPrevAccessRecord(accessQueue.last, accessQueue.first);

  setNextAccessRecord(accessQueue.last, accessQueue.first);
  setPrevAccessRecord(accessQueue.first, accessQueue.last);

  accessQueue.current = accessQueue.first;

  accessQueue.size = 0;

  return accessQueue;
}

void addToAccessQueue(struct AccessQueue *accessQueue,
                      struct AccessRecord *accessRecord) {

  if (!isInAccessQueue(accessRecord)) {

    setPrevAccessRecord(accessRecord, getPrevAccessRecord(accessQueue->last));
    setNextAccessRecord(getPrevAccessRecord(accessQueue->last), accessRecord);

    setPrevAccessRecord(accessQueue->last, accessRecord);
    setNextAccessRecord(accessRecord, accessQueue->last);

    setIsInAccessQueue(accessRecord);

    accessQueue->size++;

  } else if (accessQueue->updateOnAccess) {

    setPrevAccessRecord(getNextAccessRecord(accessRecord),
                        getPrevAccessRecord(accessRecord));
    setNextAccessRecord(getPrevAccessRecord(accessRecord),
                        getNextAccessRecord(accessRecord));

    setPrevAccessRecord(accessRecord, getPrevAccessRecord(accessQueue->last));
    setNextAccessRecord(getPrevAccessRecord(accessQueue->last), accessRecord);

    setPrevAccessRecord(accessQueue->last, accessRecord);
    setNextAccessRecord(accessRecord, accessQueue->last);
  }
}

struct AccessRecord *popFromAccessQueue(struct AccessQueue *accessQueue) {

  if (getNextAccessRecord(accessQueue->first) != accessQueue->last) {

    if (accessQueue->clock) {

      while (accessQueue->current == accessQueue->first ||
             accessQueue->current == accessQueue->last ||
             getAccessRecordSecondChance(accessQueue->current)) {

        unsetAccessRecordSecondChance(accessQueue->current);

        accessQueue->current = getNextAccessRecord(accessQueue->current);
      }

      setPrevAccessRecord(getNextAccessRecord(accessQueue->current),
                          getPrevAccessRecord(accessQueue->current));
      setNextAccessRecord(getPrevAccessRecord(accessQueue->current),
                          getNextAccessRecord(accessQueue->current));

      unsetIsInAccessQueue(accessQueue->current);
      unsetAccessRecordSecondChance(accessQueue->current);

      struct AccessRecord *accessRecord = accessQueue->current;

      accessQueue->current = getNextAccessRecord(accessQueue->current);

      return accessRecord;

    } else {

      struct AccessRecord *accessRecord =
          getNextAccessRecord(accessQueue->first);

      setPrevAccessRecord(getNextAccessRecord(accessRecord),
                          getPrevAccessRecord(accessRecord));
      setNextAccessRecord(getPrevAccessRecord(accessRecord),
                          getNextAccessRecord(accessRecord));

      unsetIsInAccessQueue(accessRecord);

      return accessRecord;
    }
  }

  return NULL;
}

void destroyAccessQueue(struct AccessQueue *accessQueue) {

  struct AccessRecord *current = accessQueue->first;

  while (current != NULL) {
    struct AccessRecord *next = current->next;

    free(current);

    current = next;

    if (current == accessQueue->first) {
      break;
    }
  }
}
