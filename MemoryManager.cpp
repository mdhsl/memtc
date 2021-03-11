//
//

#include "MemoryManager.h"
#include <iostream>

using namespace std;

MemoryManager::MemoryManager() {
    maxbytes = 1024 * 1024 * 1024L * 16; //16GB default
    minbytes = maxbytes * 40 / 100;
    // start freeing after getting 40% of max free bytes
}
void MemoryManager::setRate(double rate) {
    MallocExtension::instance()->SetMemoryReleaseRate(rate);
}

void MemoryManager::setMaxBytes(long bytes) {
    maxbytes = bytes;
    minbytes = maxbytes * 40 / 100L;
    criticalbytes = maxbytes * 80 / 100L;
}

void MemoryManager::setMinBytes(long bytes) {
    minbytes = bytes;
}

void MemoryManager::setCriticalBytes(long bytes) {
    criticalbytes = bytes;
}

size_t free_bytes_value = 1024*1024*256L;

void MemoryManager::displayMemoryInfos() {
    size_t current_allocated_bytes{};
    size_t heap_size{};
    size_t total_physical_bytes{};
    size_t transfer_cache_free_bytes{};
    size_t pageheap_free_bytes{};
    size_t pageheap_unmapped_bytes{};

    MallocExtension::instance()->GetNumericProperty("generic.current_allocated_bytes",&current_allocated_bytes);
    MallocExtension::instance()->GetNumericProperty("generic.heap_size",&heap_size);
    MallocExtension::instance()->GetNumericProperty("generic.total_physical_bytes",&total_physical_bytes);
    MallocExtension::instance()->GetNumericProperty("tcmalloc.transfer_cache_free_bytes",&transfer_cache_free_bytes);
    MallocExtension::instance()->GetNumericProperty("tcmalloc.pageheap_free_bytes",&pageheap_free_bytes);
    MallocExtension::instance()->GetNumericProperty("tcmalloc.pageheap_unmapped_bytes",&pageheap_unmapped_bytes);
    MallocExtension::instance()->GetNumericProperty("tcmalloc.pageheap_free_bytes",&pageheap_free_bytes);
//
    cout << "current_allocated_bytes: " << (current_allocated_bytes/(1024*1024)) << "m" << endl;
    cout << "heap_size: " << (heap_size/(1024*1024)) << "m" << endl;
    cout << "total_physical_bytes: " << (total_physical_bytes/(1024*1024)) << "m" << endl;
    cout << "transfer_cache_free_bytes: " << (transfer_cache_free_bytes/(1024*1024)) << "m" << endl;
    cout << "pageheap_unmapped_bytes: " << (pageheap_unmapped_bytes/(1024*1024)) << "m" << endl;
    cout << "pageheap_free_bytes: " << (pageheap_free_bytes/(1024*1024)) << "m" << endl;

}

void MemoryManager::tryRelease(bool force)  {
    size_t pageheap_free_bytes{};
    MallocExtension::instance()->GetNumericProperty("tcmalloc.pageheap_free_bytes",&pageheap_free_bytes);

    cerr << "max: pageheap_free_bytes: " << (pageheap_free_bytes/(1024*1024)) << "m" << endl;
    cerr << "maxbytes: " << maxbytes/(1024*1024) << "m" << endl;
    cerr << "criticalbytes: " << criticalbytes/(1024*1024) << "m" << endl;
    cerr << "minbytes: " << minbytes/(1024*1024) << "m" << endl;

    if(force || pageheap_free_bytes >= maxbytes) {
        // cross the MAX limit, force release the while free bytes -> slower than incremental releasing
        cerr << ">> max: pageheap_free_bytes: " << (pageheap_free_bytes/(1024*1024)) << "m" << endl;
        MallocExtension::instance()->ReleaseFreeMemory();
    } else if (pageheap_free_bytes > criticalbytes) {
        cerr << ">> critical: pageheap_free_bytes: " << (pageheap_free_bytes/(1024*1024)) << "m" << endl;
        // incremental releasing: 80% of maxbytes
        MallocExtension::instance()->ReleaseToSystem(free_bytes_value*2L);
    } else if (pageheap_free_bytes > minbytes) {
        // incremental releasing: 40% of maxbytes
        cerr << ">> incremental: pageheap_free_bytes: " << (pageheap_free_bytes/(1024*1024)) << "m" << endl;
        MallocExtension::instance()->ReleaseToSystem(free_bytes_value);
    }
}