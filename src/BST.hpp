#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <string>
#include "Player.hpp"

// Leaderboard: left = lower rating, right = higher rating
class BST {
private:
    struct Node {
        Player* player;
        Node* left;
        Node* right;
        Node(Player* player) : player(player), left(nullptr), right(nullptr) {}
    };

    Node* root;
    std::size_t count;

    bool goesLeftOf(Player* a, Player* b) const;
    void printHighToLow(Node* node, int& rank) const;
    void printRange(Node* node, int low, int high, int& found) const;
    void destroy(Node* node);

public:
    BST();
    ~BST();

    void insert(Player* player);
    bool remove(Player* player); // call BEFORE changing player->rating
    void displayLeaderboard() const;
    int displayRange(int low, int high) const; // returns how many players were printed
    std::size_t size() const;
    bool isEmpty() const;
};


inline BST::BST() : root(nullptr), count(0) {}

inline BST::~BST() {
    destroy(root);
}

// True if a belongs on the left side of b
// Same rating: the name later in the alphabet goes left,
// because the leaderboard prints right side first, so names show A to Z
inline bool BST::goesLeftOf(Player* a, Player* b) const {
    if (a->rating != b->rating) {
        return a->rating < b->rating;
    }
    return a->username > b->username;
}

// Walk down until there is an empty spot, then attach the new node there
inline void BST::insert(Player* player) {
    if (player == nullptr) return;

    Node* newNode = new Node(player);
    count++;

    if (root == nullptr) {
        root = newNode;
        return;
    }

    Node* current = root;
    while (true) {
        if (goesLeftOf(player, current->player)) {
            if (current->left == nullptr) {
                current->left = newNode;
                return;
            }
            current = current->left;
        } else {
            if (current->right == nullptr) {
                current->right = newNode;
                return;
            }
            current = current->right;
        }
    }
}

// call BEFORE changing player->rating, because the search below follows the rating
inline bool BST::remove(Player* player) {
    if (player == nullptr) return false;

    // Step 1: find the node, and remember its parent
    Node* parent = nullptr;
    Node* current = root;
    while (current != nullptr && current->player->username != player->username) {
        parent = current;
        if (goesLeftOf(player, current->player)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) return false; // not in the tree

    // Step 2: two children
    // Copy in the next player up (leftmost of the right side), then delete that node instead
    if (current->left != nullptr && current->right != nullptr) {
        Node* nextParent = current;
        Node* next = current->right;
        while (next->left != nullptr) {
            nextParent = next;
            next = next->left;
        }

        current->player = next->player;
        parent = nextParent;
        current = next;
    }

    // Step 3: current now has one child at most, so connect that child to the parent
    Node* child = current->left;
    if (child == nullptr) {
        child = current->right;
    }

    if (parent == nullptr) {
        root = child; // removing the root
    } else if (parent->left == current) {
        parent->left = child;
    } else {
        parent->right = child;
    }

    delete current;
    count--;
    return true;
}

// right, node, left = highest rating first
inline void BST::printHighToLow(Node* node, int& rank) const {
    if (node == nullptr) return;

    printHighToLow(node->right, rank);
    std::cout << rank++ << ". " << node->player->username
              << " (" << node->player->rating << ")\n";
    printHighToLow(node->left, rank);
}

// Same order as printHighToLow, but skips sides that can't have a rating in range
inline void BST::printRange(Node* node, int low, int high, int& found) const {
    if (node == nullptr) return;

    int rating = node->player->rating;

    if (rating <= high) {
        printRange(node->right, low, high, found);
    }
    if (rating >= low && rating <= high) {
        std::cout << node->player->username << " (" << rating << ")\n";
        found++;
    }
    if (rating >= low) {
        printRange(node->left, low, high, found);
    }
}

// frees nodes only, never Players (HashTable owns them)
inline void BST::destroy(Node* node) {
    if (node == nullptr) return;

    destroy(node->left);
    destroy(node->right);
    delete node;
}

inline void BST::displayLeaderboard() const {
    int rank = 1;
    printHighToLow(root, rank);
}

inline int BST::displayRange(int low, int high) const {
    int found = 0;
    printRange(root, low, high, found);
    return found;
}

inline std::size_t BST::size() const {
    return count;
}

inline bool BST::isEmpty() const {
    return count == 0;
}

#endif
