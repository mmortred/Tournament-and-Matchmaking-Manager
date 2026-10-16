#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <string>

#include <Player.hpp>

class BST{
    private:
        struct Node{
            Player* player;
            
            Node* left;
            Node* right;
            Node(Player* player): player(player), left(nullptr), right(nullptr) {}
        };

        Node* root;
        size_t count;
        
        //higher rating or tie breaking alphabetically
        bool comesBefore(Player* p1, Player* p2) const {
        if (p1->rating != p2->rating) {
            return p1->rating > p2->rating; // Primary key: Higher ELO comes first
        }
        return p1->username < p2->username; // tie breaker comapres the ASCII value of characters
            //lower ascii value means first
        }


        Node* InsertBST(Node* node, Player* player){
            if(node == nullptr){
                return new Node(player);
            }
            if(comesBefore(player, node->player)){ //check rating of new node and current tree
                node->left = InsertBST(node->left, player);
            }else{
                node->right = InsertBST(node->right, player);
            }
            return node;
        }
        
        //recursion
        Node* findMin(Node* node){
            //base case
            if(!node || !node->left){
                return node;
            }
            return findMin(node->left);
        }


        Node* removeHelper(Node* node,  Player* player , bool& removed){
          
        }

    public:
};




#endif