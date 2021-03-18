#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

std::mutex g_mutex;
bool g_ready = false;
int g_data = 0;

int produceData() {
    int randomNumber = rand() % 1000;
    std::cout << "produce data: " << randomNumber << "\n";
    return randomNumber;
}

void consumeData(int data) {
    std::cout << "receive data: " << data << "\n";
}

/**
 * Consumer thread function
 */
void consumerFunction() {
    while (true) {
        while (!g_ready) {
            // sleep for 1 second
            std::cout << "Consumer will wait 1sec\n";
            std::this_thread::sleep_for (std::chrono::seconds(1));
        }
        std::unique_lock<std::mutex> ul(g_mutex);
        consumeData(g_data);
        g_ready = false;        
    }
}

/**
 * Producer thread function
 */
void producerFunction() {
    while (true) {
        std::unique_lock<std::mutex> ul(g_mutex);

        g_data = produceData();
        g_ready = true;
        ul.unlock();
        while (g_ready) {
            // sleep for 1 second
            std::cout << "Producer will wait 1sec\n";
            std::this_thread::sleep_for (std::chrono::seconds(1));
        }
        
    }
}

void consumerThread() {
    consumerFunction();
}

void producerThread() {
    producerFunction();
}

int main() {
    std::cout << "Consumer producer problem solved using mutex" << "\n";

    std::thread t1(consumerThread);
    std::thread t2(producerThread);
    t1.join();
    t2.join();

    return 0;
}