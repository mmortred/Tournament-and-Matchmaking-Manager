#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <string>

// One match in a player's history
struct MatchRecord {
    int match_id;
    std::string opponent;
    std::string outcome;    // "WIN" or "LOSS"
    int rating_change;      // +10 or -10

    MatchRecord(int match_id = 0, const std::string& opponent = "", const std::string& outcome = "", int change = 0):
                match_id(match_id), opponent(opponent), outcome(outcome), rating_change(change) {}
};


class LinkedList {
private:
    struct Node {
        MatchRecord record;
        Node* prev;
        Node* next;

        Node(const MatchRecord& record) : record(record), prev(nullptr), next(nullptr) {}
    };

    Node* head;        
    Node* tail;        
    std::size_t count;  

public:
    LinkedList();
    ~LinkedList();

    void append(const MatchRecord& record);
    bool removeLast();
    void display() const;
    std::size_t size() const;
    bool isEmpty() const;
};


inline LinkedList::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

inline LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

// Add the newest match at the end
inline void LinkedList::append(const MatchRecord& record) {
    Node* newNode = new Node(record);

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

// Remove the newest match, used by undo
inline bool LinkedList::removeLast() {
    if (tail == nullptr) return false;

    Node* toDelete = tail;

    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr; // that was the only match
    }

    delete toDelete;
    count--;
    return true;
}

// Print oldest to newest
inline void LinkedList::display() const {
    if (head == nullptr) {
        std::cout << "(no matches yet)\n";
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        std::cout << "Match #" << current->record.match_id
                  << " vs " << current->record.opponent
                  << " - " << current->record.outcome << " (";

        if (current->record.rating_change > 0) {
            std::cout << "+";
        }
        std::cout << current->record.rating_change << ")\n";

        current = current->next;
    }
}

inline std::size_t LinkedList::size() const {
    return count;
}

inline bool LinkedList::isEmpty() const {
    return count == 0;
}

#endif
