#ifndef INDEX_H
#define INDEX_H

#include "argParser.h"
#include "assert.h"
#include "pageTable.h"

#ifndef VIRTUAL_MEMORY_KB
// 2^22 KB
#define VIRTUAL_MEMORY_KB 4194304
#endif

struct PageTable *runVirutalMemorySimulator(int argc, char **argv);

#endif