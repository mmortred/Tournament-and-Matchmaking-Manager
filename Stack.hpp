#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>
#include <string>

struct MatchUndoRecord {
    int match_id;
    std::string winner;
    std::string loser;

    int winnerPrevRating;
    int winnerPrevWins;

    int loserPrevRating;
    int loserPrevLosses;

    MatchUndoRecord(int match_id, const std::string& winner = "", const std::string& loser = "",
                    int w_rating = 0, int w_wins = 0,
                    int l_rating = 0, int l_loses = 0)
                    : match_id(match_id),
                      winner(winner),
                      loser(loser),
                      winnerPrevRating(w_rating),
                      winnerPrevWins(w_wins),
                      loserPrevRating(l_rating),
                      loserPrevLosses(l_loses) {}
};

class Stack{
    private:

        struct Node{
            MatchUndoRecord snapshot;
            Node* next;
            Node(const MatchUndoRecord& rec): snapshot(rec), next(nullptr) {}

        };
        Node* topNode;
        size_t count;
    public:

        Stack(): topNode(nullptr), count (0) {}
        ~Stack(){
            while(topNode){
                Node* toDelete = topNode;
                topNode = topNode -> next;
                delete toDelete;
            }
            count = 0;
        }

        void push(const MatchUndoRecord& record){
            Node* newNode = new Node(record);
            newNode->next = topNode;
            topNode = newNode;
            count++;
        }

        bool pop(MatchUndoRecord& outRecord){
            if (isEmpty()) return false;
            
            Node* toDelete = topNode;
            outRecord = toDelete->snapshot;
            topNode = topNode -> next;

            delete toDelete;
            count--;
            return true;
        }
        bool isEmpty() const{
            if(!topNode) return true;
            return false;
        }
        size_t size() const{
            return count;
        }
        bool peek(MatchUndoRecord& outRecord) const{
            if (isEmpty()) return false;
            outRecord = topNode -> snapshot;
            return true;
        }

};

#endif