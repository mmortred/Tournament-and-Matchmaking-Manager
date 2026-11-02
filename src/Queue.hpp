#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <string>
#include "Player.hpp"

//doubly linked list so matched players can be removed from any position 
class Queue {
private:
    struct Node {
        Player* player; 
        Node* prev;
        Node* next;

        Node(Player* player) : player(player), prev(nullptr), next(nullptr) {}
    };

    Node* head;         
    Node* tail;      
    std::size_t count;  

public:
    // Constructor
    Queue() : head(nullptr), tail(nullptr), count(0) {}

    ~Queue() {
        Node* current = head;
        while (current != nullptr) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }

    // Add player to the back of the queue 
    void enqueue(Player* player) {
        if (player == nullptr) return;

        Node* newNode = new Node(player);
        if (tail == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }


    Player* dequeue() {
        if (head == nullptr) return nullptr;

        Node* toDelete = head;
        Player* player = toDelete->player;

        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }

        delete toDelete;
        count--;
        return player;
    }

    // Peek 
    Player* front() const {
        if (head == nullptr) return nullptr;
        return head->player;
    }

    // Unlink a player from any position 
    bool removeAtPos(Player* player) {
        Node* current = head;
        while (current != nullptr) {
            if (current->player == player) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }

                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }

                delete current;
                count--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Find the waiting player with the closest rating to p1 (p1 itself is skipped)
    // maxGap < 0 means no limit (3A fallback), ties go to whoever joined earlier
    Player* findClosest(Player* p1, int maxGap) const {
        if (p1 == nullptr) return nullptr;

        Player* best = nullptr;
        int bestGap = 0;

        Node* current = head;
        while (current != nullptr) {
            if (current->player != p1) {
                int gap = current->player->rating - p1->rating;
                if (gap < 0) gap = -gap;

                if ((maxGap < 0 || gap <= maxGap) && (best == nullptr || gap < bestGap)) {
                    best = current->player;
                    bestGap = gap;
                }
            }
            current = current->next;
        }
        return best;
    }


    void display() const {
        std::cout << "\n============== LOBBY QUEUE ==============\n";
        if (head == nullptr) {
            std::cout << "(empty)\n";
        } else {
            std::cout << "FRONT -> ";
            Node* current = head;
            while (current != nullptr) {
                std::cout << current->player->username << " (" << current->player->rating << ") <-> ";
                current = current->next;
            }
            std::cout << "BACK\n";
        }
        std::cout << "=========================================\n";
    }

    std::size_t size() const { return count; }
    bool isEmpty() const { return count == 0; }
};

#endif // QUEUE_HPP
