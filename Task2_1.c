#include <pthread.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <random>
#include <thread>

struct thread_primitives {
    pthread_mutex_t mutex_shared = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutexForProducer = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t CondVal_produced = PTHREAD_COND_INITIALIZER;
    pthread_cond_t CondVal_consumed = PTHREAD_COND_INITIALIZER;
};

__thread int partial_amount = 0;

bool inWork = true;

unsigned int Consumer_quantity;
int upper_limit_ofSleep_cons = 0;

pthread_barrier_t consumers_barrier;
std::vector<pthread_t> consumers;

thread_primitives primitives;

int main(int argc, char *argv[]) {
    Consumer_quantity = static_cast<unsigned int>(std::stoi(argv[1]));
    upper_limit_ofSleep_cons = std::stoi(argv[2]);

    std::cout << run_threads() << std::endl;
    return 0;
}

void* consumer_routine(void* arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    pthread_barrier_wait(&consumers_barrier);

    int* pointerToShared_var = static_cast<int*>(arg);
    while (inWork) {
        pthread_mutex_lock(&primitives.mutex_shared);

        while (inWork && *pointerToShared_var == 0) {
            pthread_cond_wait(&primitives.CondVal_produced, &primitives.mutex_shared);
        }

        partial_amount += *pointerToShared_var;
        *pointerToShared_var = 0;

        pthread_mutex_lock(&primitives.mutexForProducer);
        pthread_cond_signal(&primitives.CondVal_consumed);
        pthread_mutex_unlock(&primitives.mutexForProducer);

        pthread_mutex_unlock(&primitives.mutex_shared);

        std::this_thread::sleep_for(std::chrono::milliseconds(get_random_integer(0, upper_limit_ofSleep_cons)));
    }

    return &partial_amount;
}

void* consumer_interruptor_routine(void* arg) {
    pthread_barrier_wait(&consumers_barrier);

    while (inWork) {
        pthread_cancel(consumers[get_random_integer(0, Consumer_quantity - 1)]);
    }

    return nullptr;
}

void* producer_routine(void* arg) {
    pthread_barrier_wait(&consumers_barrier);

    int* pointerToShared_var = static_cast<int*>(arg);
    std::string input;
    std::getline(std::cin, input);
    std::stringstream ss(input);

    int n;
    while (ss >> n) {
        pthread_mutex_lock(&primitives.mutex_shared);
        *pointerToShared_var = n;
        pthread_cond_signal(&primitives.CondVal_produced);
        pthread_mutex_unlock(&primitives.mutex_shared);

        pthread_mutex_lock(&primitives.mutexForProducer);    
        while (*pointerToShared_var != 0) {
            pthread_cond_wait(&primitives.CondVal_consumed, &primitives.mutexForProducer);
        }
        pthread_mutex_unlock(&primitives.mutexForProducer);
    }

    pthread_mutex_lock(&primitives.mutex_shared);
    inWork = false;
    pthread_cond_broadcast(&primitives.CondVal_produced);
    pthread_mutex_unlock(&primitives.mutex_shared);

    return nullptr;
}

int run_threads() {
    pthread_barrier_init(&consumers_barrier, nullptr, Consumer_quantity + 2);

    int updates_variable = 0;

    pthread_t producer, interrupter;
    pthread_create(&producer, nullptr, producer_routine, &updates_variable);
    consumers = std::vector<pthread_t>(Consumer_quantity);
    for (auto& consumer : consumers) {
        pthread_create(&consumer, nullptr, consumer_routine, &updates_variable);
    }
    pthread_create(&interrupter, nullptr, consumer_interruptor_routine, nullptr);

    pthread_join(producer, nullptr);
    pthread_join(interrupter, nullptr);

    int res = 0;
    for (auto& consumer : consumers) {
        int* value;
        pthread_join(consumer, (void **) &value);
        res += *value;
    }

    return res;
}

int get_random_integer(int lower_limit, int upper_limit) {
    std::random_device dev;
    std::mt19937 generator(dev());
    std::uniform_int_distribution<int> distribution(lower_limit, upper_limit);
    return distribution(generator);
}   
    
 



