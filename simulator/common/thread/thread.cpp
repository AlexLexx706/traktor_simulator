#include "thread.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <sys/time.h>

void * thread_fun(void * data) {
    static_cast<Thread *>(data)->run();
    return NULL;
}

long long Thread::get_timestemp_ms() {
    struct timeval te; 
    gettimeofday(&te, NULL);
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
    return milliseconds;
}

// linux realithation
struct Data {
    Thread * thread;
    pthread_t thread_id;

    Data(Thread * _thread):thread(_thread), thread_id(0){}
    ~Data(){
        join();
    }
    int start(){
        if (thread_id != 0){
            std::cerr << "cannot start thread bc thread_id != 0" << std::endl;
            return 1;
        }

        return pthread_create(
            &thread_id, NULL,
            thread_fun,
            (void *)thread);
    }

    int join(){
        if (thread_id == 0) {
            std::cerr << "cannot join thread bc thread_id == 0" << std::endl;
            return 1;
        }
        pthread_join(thread_id, NULL);
        thread_id=0;
        return 0;
    }
    bool is_active(){
        return thread != 0;
    }
};


Thread::Thread():
    data((void *)new Data(this)){
}

Thread::~Thread(){
    delete static_cast<Data*>(data);
}

int Thread::start(){
    return static_cast<Data*>(data)->start();
}

int Thread::join() {
    return static_cast<Data*>(data)->join();
}

bool Thread::is_active() const{
    return static_cast<Data*>(data)->is_active();   
}

void Thread::run(){
}

void Thread::sleep(unsigned int usec){
    //linux def
    usleep(usec);    
}


struct MutexData{
    pthread_mutex_t mutex;
    MutexData(){
        pthread_mutex_init(&mutex, NULL);
    }

    ~MutexData(){
        pthread_mutex_destroy(&mutex);   
    }

    void lock(){
        pthread_mutex_lock(&mutex);
    }

    void unlock(){
        pthread_mutex_unlock(&mutex);
    }
};

Mutex::Mutex():
    data(new MutexData()){
}

Mutex::~Mutex(){
    delete static_cast<MutexData *>(data);
}

void Mutex::lock(){
    static_cast<MutexData *>(data)->lock();
}

void Mutex::unlock(){
    static_cast<MutexData *>(data)->unlock();
}
