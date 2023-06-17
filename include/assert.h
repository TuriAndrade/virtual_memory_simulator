#ifndef ASSERT_H
#define ASSERT_H

#include <stdio.h>
#include <stdlib.h>

#define warningAssert(exp, msg)                                                \
  ((void)((exp) ? 0 : __warningAssert(#exp, __FILE__, __LINE__, msg)))

#define __warningAssert(exp, file, line, msg)                                  \
  ((void)fprintf(stderr, "%s:%u: Warning: [%s] -> %s\n", file, line, exp,      \
                 msg),                                                         \
   0)

#define errorAssert(exp, msg)                                                  \
  ((void)((exp) ? 0 : __errorAssert(#exp, __FILE__, __LINE__, msg)))

#define __errorAssert(exp, file, line, msg)                                    \
  ((void)fprintf(stderr, "%s:%u: Error: [%s] -> %s\n", file, line, exp, msg),  \
   exit(1))

#endif