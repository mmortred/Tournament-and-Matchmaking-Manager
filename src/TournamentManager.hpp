#ifndef TOURNAMENTMANAGER_HPP
#define TOURNAMENTMANAGER_HPP

#include <iostream>
#include <string>   

//1
#include "Player.hpp"
#include "HashTable.hpp"
//2
#include "BST.hpp"
//3
#include "Queue.hpp"
//4
#include "Stack.hpp"
class TournamentManager{
    private:
        HashTable playerRegistry; // 1
        BST leaderboard; // 2
        Queue lobby; //3

        //4 
        Stack undoStack;
        Player* matchP2 = nullptr;
        Player* matchP1 = nullptr;
        int nextMatchId = 1;
        



    public:
        // on
        TournamentManager() = default;
        // off
        ~TournamentManager() = default;

        bool registerPlayer(const std::string& username);//1
        bool joinLobby(const std::string& username); //2
        bool processMatchmaking(); //3
        bool recordResult(int winnerChoice); //4
        bool undoLastResult(); //5
        void displayLeaderboard() const; //6
        void displayRange(int low, int high) const; //7
        bool lookupPlayer(const std::string& username) const;

        
        void displayRegistry() const;
        void displayLobby() const;
        bool displayCurrentMatch() const;
};


 bool TournamentManager::registerPlayer(const std::string& username){
            //username length validator
            if(username.empty() || username.length() > 16){
                std::cout << "Error: Username length must be between 1 to 16 characters.\n";
                return false;
            }

            // check if available
            if (playerRegistry.contains(username)){
                std::cout << "Error: Username is already taken.\n";
                return false;
            }

            Player* newPlayer = new Player(username);
            if (playerRegistry.insert(newPlayer)){
                leaderboard.insert(newPlayer);
                std::cout << "Success: Registered (Rating 500)\n";
                return true;
            }else{
                std::cout << "Error: Failed to insert " << username << "\n";
                delete newPlayer;
                return false;
            }
        }

bool TournamentManager::joinLobby(const std::string& username){
    Player *p = playerRegistry.search(username);
    if(!p){
        std::cout << "Username not found." << "\n";
        return false;
    }
    if(p->in_lobby){
        std::cout << "Already in lobby" << "\n";
        return false;
    }
    lobby.enqueue(p);
    p->in_lobby = true;
    return true;
}

bool TournamentManager::processMatchmaking(){

    if(matchP1){
        std::cout << "Record the current match first.\n";
        return false;
    }

    if(lobby.size() <= 1){
        std::cout << "Insufficient player." << "\n";
        return false;
    }
    Player* p1 = lobby.front();
    Player* p2 = lobby.findClosest(p1, 50);

    //if no one within 50
    if(!p2 && lobby.size() >= 10){
        p2 = lobby.findClosest(p1, -1); //find who the smallest gap
    }

    if(!p2){
        std::cout << "No MatchFound within +-50 Rating." << "\n";
        return false;
    }

    lobby.dequeue();
    lobby.removeAtPos(p2);
    p1->in_lobby = false;
    p2->in_lobby = false;

    std::cout << "Match Formed: " << p1->username << " vs " << p2->username << "\n";
    matchP1 = p1;
    matchP2 = p2;
    return true;
}

bool TournamentManager::recordResult(int winnerChoice){
    if(!matchP1){
        std::cout << "No match to record. \n";
        return false;
    }
    Player* winner = nullptr;
    Player* loser = nullptr;
    if(winnerChoice == 1){
        winner = matchP1;
        loser = matchP2;
    }else if(winnerChoice == 2){
        winner = matchP2;
        loser = matchP1;
    }else{
        std::cout << "Error: Enter 1 or 2.\n";
        return false;
    }

    leaderboard.remove(winner);
    leaderboard.remove(loser);
    winner->rating += 10;
    loser->rating -= 10;

    winner->wins++;
    loser->losses++;

    leaderboard.insert(winner);
    leaderboard.insert(loser);

    int id = nextMatchId++;


    undoStack.push({id, winner, loser});

    
    winner->history.append(MatchRecord(id, loser->username, "WIN", 10));
    loser->history.append(MatchRecord(id, winner->username, "LOSS", -10));


    matchP1 = nullptr;
    matchP2 = nullptr;
    std::cout << "Match #" << id << ": " << winner->username << " beat " << loser->username << "\n";
    return true;
}


bool TournamentManager::undoLastResult(){
    MatchResult last;
    if(!undoStack.pop(last)){
        std::cout << "No result to undo.\n";
        return false;
    }

    Player* winner = last.winner;
    Player* loser = last.loser;

    // remove BEFORE changing the ratings, same as recordResult
    leaderboard.remove(winner);
    leaderboard.remove(loser);

    winner->rating -= 10;
    loser->rating += 10;
    winner->wins--;
    loser->losses--;

    leaderboard.insert(winner);
    leaderboard.insert(loser);

    // the newest history entry of each player is this match
    winner->history.removeLast();
    loser->history.removeLast();

    std::cout << "Undid Match #" << last.match_id << ": " << winner->username << " (" << winner->rating << "), "
              << loser->username << " (" << loser->rating << ")\n";
    return true;
}


void TournamentManager::displayLeaderboard() const{
        if(leaderboard.isEmpty()){ 
            std::cout << "No players registered yet.\n";
            return;
        }
        leaderboard.displayLeaderboard();
}

void TournamentManager::displayRange(int low, int high) const {
    if(low > high){
        std::cout << "Error: Lowest rating cannot be above highest rating.\n";
        return;
    }
    if(leaderboard.displayRange(low, high) == 0){
        std::cout << "No players between " << low << " and " << high << ".\n";
    }
}

bool TournamentManager::lookupPlayer(const std::string& username) const{
    Player* p = playerRegistry.search(username);
    if(!p){
        std::cout << "Player not found.\n";
        return false;
    }
    std::cout << "\n-----Player Profile-----\n";
    std::cout << "Username: " << p->username << "\n";
    std::cout << "Rating: " << p->rating << "\n";
    std::cout << "Record: " << p->wins << " W - " << p->losses << " L\n";

    if (p->in_lobby){
        std::cout << "In lobby: YES\n";
    }else{
        std::cout << "In lobby: NO\n";

    }

    std::cout << "Match History: \n";
    p->history.display();
    return true;
}



void TournamentManager::displayRegistry() const {
    playerRegistry.display();
}

void TournamentManager::displayLobby() const {
    lobby.display();
}

// Shows who is playing, returns false if there is no match to record
bool TournamentManager::displayCurrentMatch() const {
    if(!matchP1){
        std::cout << "No match to record. \n";
        return false;
    }
    std::cout << "Player 1: " << matchP1->username << " (" << matchP1->rating << ")\n";
    std::cout << "Player 2: " << matchP2->username << " (" << matchP2->rating << ")\n";
    return true;
}

#endif