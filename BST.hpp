#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <string>

// Include Player.hpp for master Player record definition
#include "Player.hpp"

class BST {
private:
    // Privately nested node storing Player pointer (SRS Requirement)
    struct Node {
        Player* player; // Master record owned by Hash Table
        Node* left;
        Node* right;

        Node(Player* p) : player(p), left(nullptr), right(nullptr) {}
    };

    Node* root;
    size_t count;

    // Composite key tie-breaker helper (SRS Req 1A)
    // Returns true if p1 ranks HIGHER than p2 (Higher rating, or tie-break alphabetically)
    bool comesBefore(Player* p1, Player* p2) const {
        if (p1->rating != p2->rating) {
            return p1->rating > p2->rating; // Primary key: Higher ELO ranks first
        }
        return p1->username < p2->username; // Secondary tie-breaker: Alphabetical order
    }

    // Helper for recursive insertion
    Node* insertHelper(Node* node, Player* player) {
        if (!node) {
            return new Node(player);
        }

        if (comesBefore(player, node->player)) {
            node->left = insertHelper(node->left, player);
        } else {
            node->right = insertHelper(node->right, player);
        }
        return node;
    }

    // Helper to find minimum node in subtree (In-order successor)
    Node* findMin(Node* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    // Helper for recursive removal
    Node* removeHelper(Node* node, Player* player, bool& removed) {
        if (!node) return nullptr;

        if (node->player == player) {
            removed = true;
            // Case 1: No left child
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } 
            // Case 2: No right child
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Two children -> Replace with in-order successor
            Node* minRight = findMin(node->right);
            node->player = minRight->player;
            node->right = removeHelper(node->right, minRight->player, removed);
        } else if (comesBefore(player, node->player)) {
            node->left = removeHelper(node->left, player, removed);
        } else {
            node->right = removeHelper(node->right, player, removed);
        }

        return node;
    }

    // Helper for in-order leaderboard display (SRS Req 6)
    void printLeaderboardHelper(Node* node, int& rank) const {
        if (!node) return;

        printLeaderboardHelper(node->left, rank);

        std::cout << "  " << rank << ".\t" << node->player->username 
                  << "\tRating: " << node->player->rating 
                  << "\t(" << node->player->wins << "W / " << node->player->losses << "L)\n";
        rank++;

        printLeaderboardHelper(node->right, rank);
    }

    // Helper for range queries (SRS Req 7)
    void printRangeHelper(Node* node, int minRating, int maxRating) const {
        if (!node) return;

        if (node->player->rating <= maxRating) {
            printRangeHelper(node->left, minRating, maxRating);
        }

        if (node->player->rating >= minRating && node->player->rating <= maxRating) {
            std::cout << "  • " << node->player->username 
                      << " (" << node->player->rating << " ELO)\n";
        }

        if (node->player->rating >= minRating) {
            printRangeHelper(node->right, minRating, maxRating);
        }
    }

    // Helper for destructor cleanup
    void destroyTree(Node* node) {
        if (!node) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node; // Deletes tree node wrapper (Master Player object owned by HashTable)
    }

public:
    BST() : root(nullptr), count(0) {}

    // Destructor: Cleans up all BST node wrappers directly
    ~BST() {
        destroyTree(root);
        root = nullptr;
        count = 0;
    }

    // Insert player into leaderboard
    void insert(Player* player) {
        if (!player) return;
        root = insertHelper(root, player);
        count++;
    }

    // Remove player from leaderboard (Used prior to rating updates)
    bool remove(Player* player) {
        if (!player || !root) return false;
        bool removed = false;
        root = removeHelper(root, player, removed);
        if (removed) count--;
        return removed;
    }

    // Display all players ordered by rank (SRS Req 6)
    void printLeaderboard() const {
        if (!root) {
            std::cout << "  (Leaderboard is currently empty)\n";
            return;
        }
        int rank = 1;
        printLeaderboardHelper(root, rank);
    }

    // Display players within rating range [minRating, maxRating] (SRS Req 7)
    void printRange(int minRating, int maxRating) const {
        if (!root) {
            std::cout << "  (Leaderboard is currently empty)\n";
            return;
        }
        printRangeHelper(root, minRating, maxRating);
    }

    size_t size() const { return count; }
    bool isEmpty() const { return root == nullptr; }
};

#endif // BST_HPP