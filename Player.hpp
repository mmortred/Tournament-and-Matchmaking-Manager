#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>


// Core Data Record

struct MatchRecord{
    int match_id;
    std::string opponent;
    std::string outcome;
    int rating_change;      // +10 or -10

    MatchRecord(int match_id = 0, const std::string& opponent = "", const std::string& outcome = "", int change = 0):
                match_id(match_id), opponent(opponent), outcome(outcome), rating_change(change) {}
};

struct Player{
    std::string username;
    int rating;
    int wins;
    int losses;
    bool in_lobby;

    //LinkedList history;

    Player(const std::string& username, int rating = 500): 
           username(username), rating(rating), wins(0), losses(0), in_lobby(false) {}
};

#endif