# memtc
Memtc is a lib allowing users to control the HEAP memory. This lib is provided with its Java binding and allows to release the memory back to the OS. (based on TCMalloc).

When using C++ programs in a container context (docker, kubernetes etc..), the default allocator often sees the physical 
memory of the machine and not the memory of the container where it is located.
Thus, for a given Java program for example, the user of a C++ lib will grow the HEAP (RSS) of the OS without freeing 
it before reaching about 40% (observed) of the physical memory of the machine.

For example, if the machine has 256GB of ram, and the kubernetes pod is limited to 16GB, the RSS will continue to grow 
to 40% of 256GB before starting to release memory back to the OS.

A workaround is to use a different allocator than PTMalloc (default in linux): TCmalloc.
This allocator has features to immediately release memory and back to the OS.

Memtc is a wrapper that allows to define a strategy on three levels to free the memory:
- incremental: releases some memory if a certain threshold is exceeded (40% by default)
- critical: frees more memory if you exceed a certain threshold (80% by default)
- max: frees all the free_memory_heap if it exceeds the defined max threshold (100%)

tcmalloc: 
* https://gperftools.github.io/gperftools/tcmalloc.html
* https://github.com/google/tcmalloc

# JNI
Memtc provides the java JNI to be called directly from its Java program.

To be able to work, it is necessary to define in environment variable the TCMalloc allocator:

For example, on archlinux:

LD_PRELOAD=/usr/lib/libtcmalloc.so

and can be used like:

```bash
~ export LD_PRELOAD=/usr/lib/libtcmalloc.so
~ java.. -Djava.library.path=<path_to_the_memtc.so>
```

In your java code:

```java
...
static {
    memoryManagerJNI.SetMaxBytes(1024*1024*1024L*2L); //
    memoryManagerJNI.SetMinBytes(1024*1024*128L); // 128M

    scheduledExecutorService.scheduleAtFixedRate(() -> {
        try {
            memoryManagerJNI.TryRelease(false);
            memoryManagerJNI.DisplayMemoryInfos();
        }catch (Throwable ex) {
            ex.printStackTrace();
        }
    }, 0, 5000, TimeUnit.MILLISECONDS);
}
...
```