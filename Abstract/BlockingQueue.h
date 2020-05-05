//
// Created by pawel on 04.05.2020.
//

#ifndef TIN_BLOCKINGQUEUE_H
#define TIN_BLOCKINGQUEUE_H

#include <queue>
#include <mutex>

/**
 *  Used to communicate between Game and UdpHandler.
 *  Handler blocks on pop() until there is a command to be send.
 *
 */

template<typename T>
class BlockingQueue {
    std::queue<T> queue;
    std::mutex m;
    std::mutex empty; // locked while queue is empty - blocks pop()
public:
    BlockingQueue();
    void push(T new_element);
    T pop();
};

template<typename T>
BlockingQueue<T>::BlockingQueue() {
    empty.lock();
}

template<typename T>
void BlockingQueue<T>::push(T new_element) {
    std::lock_guard<std::mutex> guard(m);
    queue.push(new_element);
    if(queue.size() == 1)
        empty.unlock();
}

template<typename T>
T BlockingQueue<T>::pop() {
    empty.lock();
    T popped = queue.front();
    queue.pop();
    if(!queue.empty())
        empty.unlock();
    return popped;
}


#endif //TIN_BLOCKINGQUEUE_H
