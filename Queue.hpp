#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <string>

// Include Player.hpp for Player struct definition
#include "Player.hpp"

class Queue{
    private:
        struct Node{
            Player* player;
            Node* next;
            Node* prev;

            Node(Player* p): player(p), next(nullptr), prev(nullptr) {}
        };

        Node* front; //longest waiting player
        Node* rear; // newest waiting player
        size_t count;

        int getDiff(int a, int b) const{
            int diff = a - b;
            
            return (diff < 0 ) ? -diff : diff; // if less than 0 then negative
        }


    public:
        // add players at the end of the queue
        void enqueue(Player* player){
            if(!player) return;

            Node* newNode = new Node(player);
            if(!front){
                front = newNode;
                rear = newNode;
            }else{
                rear    -> next = newNode;
                newNode -> prev = rear;
                rear = newNode;
            }
            count++;
        }
        
        // dequeue at the front
        Player* dequeue(){

        }
        Player* peekFront() const{
            if(!front) return nullptr;
            return front->player;
        }

};
#endif