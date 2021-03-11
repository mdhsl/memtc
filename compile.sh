JAVA_HOME=/usr/lib/jvm/java-15-openjdk/

mkdir -p ${PWD}/dist

c++ -fPIC  \
  -I"$JAVA_HOME/include"  \
  -I"$JAVA_HOME/include/linux" \
  -lpthread  -shared  -ltcmalloc \
  -o dist/libmemtc.so  \
  memtc_memManager.cpp  \
  MemoryManager.cpp \
  -O3 -flto -std=c++17 -fpermissive
