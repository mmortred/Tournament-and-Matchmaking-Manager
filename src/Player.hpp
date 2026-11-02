#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include "LinkedList.hpp"

// Core Data Record

struct Player{
    std::string username;
    int rating;
    int wins;
    int losses;
    bool in_lobby;
    int ayahnna[10];

    LinkedList history;

    Player(const std::string& username, int rating = 500): 
           username(username), rating(rating), wins(0), losses(0), in_lobby(false) {}
};

#endif