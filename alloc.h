#ifndef ALLOC_H
#define ALLOC_H

#ifndef _STDLIB_H
#include <stdlib.h>
#endif /* _STDLIB_H */


// Validate if memory has been successfully allocated to a pointer.
// If not, exit with signal 1.
static inline void validateAlloc(void *ptr) {
    if (ptr == NULL) {
        exit(1);
    }
}


#endif /* ALLOC_H */
