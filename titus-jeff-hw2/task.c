//
//  main.cpp
//  titus-eze-hw2
//
//  Created by Admin on 30.05.2021.
//
#include <pthread.h>
#include <iostream>
#include <thread>
#include <vector>


class Value { // shared data structure
public:
    Value() : _value(0) { }

    void update(int value) {
        _value = value;
    }

    int get() const {
        return _value;
    }

private:
    int _value;
};

pthread_t thread;
pthread_mutex_t producer_mtx;
pthread_mutex_t consumer_mtx;
bool isReady = false;
bool isFinish = false;
pthread_cond_t consumer_v;
pthread_cond_t producer_v;

pthread_barrier_t consumers_barrier;
std::vector<pthread_t> consumers;

unsigned int Consumer_quantity;
int upper_limit_ofSleep_cons = 0;


void* producer_routine(void* arg) {
    pthread_barrier_wait(&consumers_barrier);
    
    int n;
    Value entity;
    
    while (std::cin >> n) {
        std::cout << n << std::endl;
        entity.update(n);
        pthread_mutex_lock(&producer_mtx);
        isReady = true;
        pthread_cond_signal(&producer_v);
        pthread_mutex_unlock(&producer_mtx);

        pthread_mutex_lock(&consumer_mtx);
        
        while (isReady) {
            pthread_cond_wait(&consumer_v,&consumer_mtx);
        }
        pthread_mutex_unlock(&consumer_mtx);
    }
    isFinish = true;
    pthread_cond_signal(&producer_v);
    return NULL;
}

 
void* consumer_routine(int* arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    pthread_barrier_wait(&consumers_barrier);
    
    Value entity;
    entity.update(*arg);
    int* sum = 0;
    
      while (!isFinish) {
          pthread_mutex_lock(&producer_mtx);
         while (!isReady && !isFinish) {
             pthread_cond_wait(&producer_v, &producer_mtx);
        }
          pthread_mutex_unlock(&producer_mtx);
          if(isFinish) break;
         sum += entity.get();
          pthread_mutex_lock(&consumer_mtx);
        isReady = false;
          pthread_cond_signal(&consumer_v);
          pthread_mutex_unlock(&consumer_mtx);
        
    }
    return sum;
}

void* consumer_interruptor_routine(void* arg) {
    pthread_barrier_wait(&consumers_barrier);
    while (!isFinish){
        pthread_cancel(*(pthread_t*)arg);
    }
    return  NULL;
}
 


int run_threads() {
    pthread_barrier_init(&consumers_barrier, nullptr, Consumer_quantity + 2);
    
    pthread_t consumer;
    pthread_t producer = nullptr;
    pthread_t interruptor;
    int updates_variable = 0;
    
    pthread_create(&producer, nullptr, producer_routine, &sum);
    consumers = std::vector<pthread_t>(Consumer_quantity);
        for (auto& consumer : consumers) {
            pthread_create(&consumer, nullptr, consumer_routine, &updates_variable);
        }
    
    pthread_create(&interruptor, nullptr, consumer_interruptor_routine, nullptr);

    
    pthread_cond_init(&consumer_v, NULL);
    pthread_cond_init(&producer_v, NULL);
    
    
    pthread_join(producer, nullptr);
    pthread_join(interruptor, nullptr);

    int sum = 0;
        for (auto& consumer : consumers) {
            int* value;
            pthread_join(consumer, (void **) &value);
            sum += *value;
        }

        return sum;
}
 

int main(int argc, char *argv[]) {
    Consumer_quantity = static_cast<unsigned int>(std::stoi(argv[1]));
    upper_limit_ofSleep_cons = std::stoi(argv[2]);

    std::cout << run_threads() << std::endl;
    return 0;
}
