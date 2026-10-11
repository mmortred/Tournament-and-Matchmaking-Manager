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

        void appendMatch(int match_id, const std::string& opponent, const std::string& outcome, int rating_change){
            MatchRecord record(match_id, opponent, outcome, rating_change);
            Node* newNode = new Node(record);
    
            if(!head){
                head  = newNode;
                tail  = newNode;
            }else{
                tail    -> next = newNode;
                newNode -> prev = tail;
                tail    = newNode;
            }
            count++;
        }

        bool deleteEnd(){
            if(!tail){ return false; }
            Node* toDelete = tail;

            if(head == tail){
                head = nullptr;
                tail = nullptr;
            }else{
                tail = tail->prev;
                tail -> next = nullptr;
            }

            delete toDelete;
            count--;
            return true;
        } 


        void displayHistory(){
            if(!head){ std::cout << "(No Match History Available)\n"; }
            
            Node* current = head;
            
            while(current){
                   std::cout << " Match" << current -> data.match_id
                             << " vs "   << current -> data.opponent
                             << "   "    << current -> data.outcome
                             << "   "    << (current -> data.rating_change >= 0 ? "+" : "")
                             << current -> data.rating_change << "\n";
                             current = current -> next;
            }


        }
        size_t size() const{
            return count;
        }
        bool isEmpty() const{
            if(!head){
                return true;
            }
            return false;
        }
    
};          


#endif