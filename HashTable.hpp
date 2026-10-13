#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <iostream>
#include <string>
#include "Player.hpp"

class HashTable {
private:
    static constexpr int SIZE = 10;

    struct Node {
        Player* player;
        Node* next;

        Node(Player* p) : player(p), next(nullptr) {}
    };

    Node* table[SIZE];

    // Calculate the array index using the username
    int hashFunction(const std::string& username) const {
        int sum = 0;

        for (char c : username) {
            sum += c;
        }

        return sum % SIZE;
    }

public:
    // Initialize every array slot as empty
    HashTable() {
        for (int i = 0; i < SIZE; i++) {
            table[i] = nullptr;
        }
    }

    // Delete the linked-list nodes when the hash table is destroyed
    ~HashTable() {
        for (int i = 0; i < SIZE; i++) {
            Node* current = table[i];

            while (current != nullptr) {
                Node* toDelete = current;
                current = current->next;

                delete toDelete;
            }

            table[i] = nullptr;
        }
    }

    // Insert a player into the hash table
    bool insert(Player* player) {
        if (player == nullptr) {
            return false;
        }

        int index = hashFunction(player->username);

        Node* current = table[index];

        // Prevent duplicate usernames
        while (current != nullptr) {
            if (current->player->username == player->username) {
                return false;
            }

            current = current->next;
        }

        // Create a new node
        Node* newNode = new Node(player);

        // Insert at the beginning of the linked list
        newNode->next = table[index];
        table[index] = newNode;

        return true;
    }

    // Find a player using their username
    Player* search(const std::string& username) const {
        int index = hashFunction(username);

        Node* current = table[index];

        while (current != nullptr) {
            if (current->player->username == username) {
                return current->player;
            }

            current = current->next;
        }

        return nullptr;
    }

    // Display every array slot and its linked list
    void display() const {
        std::cout << "\n========== HASH TABLE ==========\n";

        for (int i = 0; i < SIZE; i++) {
            std::cout << "[" << i << "] -> ";

            Node* current = table[i];

            if (current == nullptr) {
                std::cout << "EMPTY";
            }

            while (current != nullptr) {
                std::cout << current->player->username << " -> ";
                current = current->next;
            }

            std::cout << "nullptr\n";
        }

        std::cout << "================================\n";
    }
};

#endif