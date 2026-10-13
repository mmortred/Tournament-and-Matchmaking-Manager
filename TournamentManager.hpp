#ifndef TOURNAMENTMANAGER_HPP
#define TOURNAMENTMANAGER_HPP

#include <iostream>
#include <string>   

//1
#include "Player.hpp"
#include "HashTable.hpp"

class TournamentManager{
    private:
        HashTable playerRegistry;
    public:
        // on
        TournamentManager() = default;
        // off
        ~TournamentManager() = default;

        bool registerPlayer(const std::string& username){
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
                std::cout << "Success: " << username << "is registered (Default Rating: 500)\n";
                playerRegistry.display();
                return true;
            }else{
                std::cout << "Error: Failed to insert " << username << "\n";
                delete newPlayer;
                return false;
            }
        }
};




#endif