#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "Player.hpp"

// One recorded result, kept so undo knows who to reverse
struct MatchResult {
    int match_id;
    Player* winner;
    Player* loser;
};

// Undo log, the newest result is always on top
class Stack {
private:
    struct Node {
        MatchResult result;
        Node* next;     // The result below this one

        Node(const MatchResult& result) : result(result), next(nullptr) {}
    };

    Node* top;          // Newest result
    std::size_t count;  // Total results

public:
    Stack();
    ~Stack();

    void push(const MatchResult& result);
    bool pop(MatchResult& out);
    std::size_t size() const;
    bool isEmpty() const;
};


inline Stack::Stack() : top(nullptr), count(0) {}

// Only deletes nodes since players belong to the HashTable
inline Stack::~Stack() {
    while (top != nullptr) {
        Node* toDelete = top;
        top = top->next;
        delete toDelete;
    }
}

// Put a new result on top
inline void Stack::push(const MatchResult& result) {
    Node* newNode = new Node(result);
    newNode->next = top;
    top = newNode;
    count++;
}

// Copy the top result into out, then remove it. Returns false if the stack is empty
inline bool Stack::pop(MatchResult& out) {
    if (top == nullptr) return false;

    Node* toDelete = top;
    out = toDelete->result;

    top = top->next;
    delete toDelete;
    count--;
    return true;
}

inline std::size_t Stack::size() const {
    return count;
}

inline bool Stack::isEmpty() const {
    return count == 0;
}

#endif
