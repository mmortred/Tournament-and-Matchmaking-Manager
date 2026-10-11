#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <string>

#include "Player.hpp"

class LinkedList{
    private:

        struct Node{
            MatchRecord data;
            Node* next;
            Node* prev;

            Node(const MatchRecord& record):
                data(record), next(nullptr), prev(nullptr) {}
        };

        Node* head;
        Node* tail;

        size_t count;               // size_t so that only + integers are allowed (unsigned int)

    public:
        LinkedList(): head(nullptr), tail(nullptr), count(0){}
        ~LinkedList(){
            while(head){
                Node* toDelete = head;
                head = head->next;
                delete toDelete;
            }
            tail = nullptr;
            count = 0;
        }

        void appendMatch(int match_id, const std::string& opponent, const std::string& outcome, int rating_change);
        bool deleteEnd(); // 
        void displayHistory() const;
        size_t size() const;
        bool isEmpty() const;
        void clear();
        

};          
        //destructor
        inline LinkedList::~LinkedList(){
            while(head){
                Node* toDelete = head;
                head = head->next;
                delete toDelete;
            }
            tail = nullptr;
            count = 0;
        }

        // add to end
            inline void LinkedList::appendMatch(int match_id, const std::string& opponent, 
                        const std::string& outcome, int rating_change){

            MatchRecord record(match_id, opponent, outcome, rating_change);
            Node* newNode = new Node(record);
            
            if(!head){
                head    = newNode;
                tail    = newNode;
            }else{
                tail    -> next = newNode;
                newNode -> prev = tail;
                tail    = newNode;
            }
            count++;
        }
#endif