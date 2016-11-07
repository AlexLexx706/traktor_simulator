#ifndef __SIMPLE_THREAD__
#define __SIMPLE_THREAD__

class Thread{
public:
    Thread();
    ~Thread();
    int start();
    int join();
    virtual void run();
    //sleep microsecond
    static void sleep(unsigned int);
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