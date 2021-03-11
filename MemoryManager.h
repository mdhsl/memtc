//
//

#ifndef NATIVE_MEMORYMANAGER_H
#define NATIVE_MEMORYMANAGER_H

// tcmalloc
#include "gperftools/malloc_extension.h"

class MemoryManager {
public:
    MemoryManager();
    void setRate(double rate);
    void tryRelease(bool force);
    void setMaxBytes(long maxbytes);
    void setMinBytes(long minbytes);
    void setCriticalBytes(long criticalbytes);
    void displayMemoryInfos();
private:
    long maxbytes;
    long minbytes;
    long criticalbytes;
};


#endif //NATIVE_MEMORYMANAGER_H
