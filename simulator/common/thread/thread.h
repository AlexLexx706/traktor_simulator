#ifndef __SIMPLE_THREAD__
#define __SIMPLE_THREAD__

class Thread{
public:
    Thread();
    ~Thread();
    int start();
    int join();
    bool is_active() const;
    virtual void run();
    //sleep microsecond
    static void sleep(unsigned int);
    static long long get_timestemp_ms();
private: 
    void * data;
};


class Mutex;

class Mutex{
public:
    class ContextHelper {
        Mutex & mutex;
    public:
        ContextHelper(Mutex & _mutex):mutex(_mutex){
            mutex.lock();
        }
        ~ContextHelper(){
            mutex.unlock();   
        }
    };
    Mutex();
    ~Mutex();
    void lock();
    void unlock();
private:
    void * data;
};

#endif // __SIMPLE_THREAD__