#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <string>

//Matchmaking Lobby ADT
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
        void dequeue(){
            if(!front) return; 
            Node* toDelete = front;

            if(front == rear){
                front = nullptr;
                rear = nullptr;
            }else{
                front -> prev = nullptr;
                front = front -> next;
            }
            delete toDelete;
            count--;
        }

        bool attemptMatch(Player** outP1, Player** outP2) {
            if (count < 2 || !front) return false; // Minimum 2 players required

            Node* p1Node = front;
            Player* p1 = p1Node->player;

            Node* bestWithinThreshold = nullptr;
            Node* bestOverallCandidate = nullptr;

            int minThresholdGap = 999999;
            int minOverallGap = 999999;

            // Single pass through remaining lobby players
            Node* current = p1Node->next;
            while (current != nullptr) {
                int gap = getDiff(p1->rating, current->player->rating);

                // Track closest within ±50
                if (gap <= 50 && gap < minThresholdGap) {
                    minThresholdGap = gap;
                    bestWithinThreshold = current;
                }

                // Track overall closest candidate (for SRS Req 3A Fallback)
                if (gap < minOverallGap) {
                    minOverallGap = gap;
                    bestOverallCandidate = current;
                }

                current = current->next;
            }

            // Determine target candidate based on SRS v1.2 Rules
            Node* targetOpponentNode = nullptr;

            if (bestWithinThreshold != nullptr) {
                targetOpponentNode = bestWithinThreshold; // Priority 1: Match within ±50
            } else if (count >= 20) {
                targetOpponentNode = bestOverallCandidate; // Priority 2: Queue >= 20 Fallback
            }

            // No valid candidate found
            if (!targetOpponentNode) return false;

            // Assign output pointers
            *outP1 = p1;
            *outP2 = targetOpponentNode->player;

            // Unlink both matched players in O(1) time
            unlinkNode(p1Node);
            unlinkNode(targetOpponentNode);

            return true;
        }

        // Helper method to unlink any node from any position in O(1) time (SRS Req 3B)
        void unlinkNode(Node* node) {
        if (!node) return;

  
        if (node == front) {
            front = node->next;
            if (front) front->prev = nullptr;
        } else {
            node->prev->next = node->next;
        }

        if (node == rear) {
            rear = node->prev;
            if (rear) rear->next = nullptr;
        } else {
            node->next->prev = node->prev;
        }

        delete node;
        count--;
        }

        Player* peekFront() const{
            if(!front) return nullptr;
            return front->player;
        }

        size_t size() const {return count;}

        bool isEmpty() const{
            if(!front) return true;
            return false;
        }
};
#endif