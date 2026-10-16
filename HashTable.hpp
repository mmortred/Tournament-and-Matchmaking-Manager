#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <iostream>
#include <string>
#include "Player.hpp"

class HashTable {
private:
    struct Node {
        Player* player; // Pointer to Player object 
        Node* next;     // Next node in collision chain

        Node(Player* player) : player(player), next(nullptr) {}
    };

    Node** buckets;       // Dynamic array of bucket head pointers
    std::size_t capacity; // Total capacity of bucket array
    std::size_t count;    // Total registered player count


    std::size_t hashFunction(const std::string& key) const {
        std::size_t sum = 0;
        std::size_t i = 0;

        while (i < key.length()) {
            sum = sum * 31 + key[i];
            i++;
        }

        return sum % capacity;
    }

public:
    // Constructor, 101 is prime = less collision
    HashTable(std::size_t cap = 101) : capacity(cap), count(0) {
        buckets = new Node*[capacity]; 

        for(std::size_t i = 0; i < capacity; i++){
            buckets[i] = nullptr;
        }
    }

    // Destructor
    ~HashTable() {
        std::size_t i = 0;
        while (i < capacity) {
            Node* current = buckets[i];
            while (current != nullptr) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete->player; 
                delete toDelete;      
            }
            i++;
        }
        delete[] buckets; // Free dynamic bucket array
    }

    // Check if player exists by username
    bool contains(const std::string& username) const {
        std::size_t index = hashFunction(username);
        Node* current = buckets[index];

        while (current != nullptr) {
            if (current->player->username == username) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Register a new player
    bool insert(Player* player) {
        if (player == nullptr) return false;

        // Reject duplicate username
        if (contains(player->username)) {
            return false;
        }

        std::size_t index = hashFunction(player->username);

        // Insert at head of collision chain in O(1)
        Node* newNode = new Node(player);
        newNode->next = buckets[index];
        buckets[index] = newNode;

        count++;
        return true;
    }

    // Fast O(1) lookup by username
    Player* search(const std::string& username) const {
        std::size_t index = hashFunction(username);
        Node* current = buckets[index];

        while (current != nullptr) {
            if (current->player->username == username) {
                return current->player;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Display contents of active buckets for visual verification
    void display() const {
        std::cout << "\n========== HASH TABLE REGISTER ==========\n";
        std::size_t i = 0;
        while (i < capacity) {
            if (buckets[i] != nullptr) {
                std::cout << "Bucket [" << i << "] -> ";
                Node* current = buckets[i];
                while (current != nullptr) {
                    std::cout << current->player->username << " (" << current->player->rating << " RATING) -> ";
                    current = current->next;
                }
                std::cout << "nullptr\n";
            }
            i++;
        }
        std::cout << "=========================================\n";
    }

    std::size_t size() const { return count; }
    bool isEmpty() const { return count == 0; }
};

#endif // HASHTABLE_HPP