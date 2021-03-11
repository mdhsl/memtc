package memtc;

public class MemtcJNI {
    static {
        System.loadLibrary("memtc"); // Load native library libmemtc.so
        //  at runtime
        Native_init_class();
    }
    private long _native_ptr = 0;

    protected MemtcJNI(long ptr) {
        _native_ptr = ptr;
    }

    public MemtcJNI() {
        this(Native_create());
    }

    // Native methods

    private static native void Native_init_class();

    public native void Native_destroy();

    private static native long Native_create();

    public native void TryRelease(boolean force);

    public native void SetMaxBytes(long bytes);

    public native void SetMinBytes(long bytes);

    public native void SetCriticalBytes(long bytes);

    public native void DisplayMemoryInfos();

    // finalize
    @Override
    public synchronized void finalize() {
        if ((_native_ptr & 1) != 0)
        { // Resource created and not donated
            Native_destroy();
        }
    }
}
