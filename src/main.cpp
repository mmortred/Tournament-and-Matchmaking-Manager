#include <iostream>
#include <string>

#include "TournamentManager.hpp"

using namespace std;

void clearInputBuffer() {
    cin.clear();
    while (cin.get() != '\n') {
        // Discard bad input characters
    }
}

int main() {
    TournamentManager manager;
    int choice = 0;

    cout << "\n=======================================================\n";
    cout << "     WELCOME TO TOURNAMENT MATCHMAKING MANAGER         \n";
    cout << "=======================================================\n";

    while (true) {
        cout << "\n------------------ ADMIN CONSOLE MENU ------------------\n";
        cout << "  1. Register New Player              (Hash Table)\n";
        cout << "  2. Join Matchmaking Lobby Queue     (Queue)\n";
        cout << "  3. Process Matchmaking              (Queue)\n";
        cout << "  4. Record Match Outcome             (Stack)\n";
        cout << "  5. Undo Last Match Result           (Stack)\n";
        cout << "  6. Display Live Leaderboard         (BST)\n";
        cout << "  7. Query Rating Range               (BST)\n";
        cout << "  8. Lookup Player Profile & History  (Hash Table)\n";
        cout << "  9. Exit System\n";
        cout << "--------------------------------------------------------\n";
        cout << "Select Option [1-9]: ";

        if (!(cin >> choice)) {
            cout << "  [ERROR] Invalid entry. Please enter a number.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: {
                string username;
                cout << "\n--- [1] REGISTER NEW PLAYER ---\n";
                cout << "Type /x to stop.\n";
                while(true){
                    cout << "Enter username (1-16 chars): ";
                    cin >> username;
                    if (username == "/x" || username == "/X"){
                        break;// leaves the while loop only
                    }
                    manager.registerPlayer(username);
                }
                manager.displayRegistry();
                break;

            }

            case 2: {
                string username;
                cout << "\n--- [2] JOIN MATCHMAKING LOBBY ---\n";
                cout << "Type /x to stop.\n";
                manager.displayRegistry();

                while (true) {
                    cout << "Enter username: ";
                    cin >> username;
                    if (username == "/x" || username == "/X") {
                        break; 
                    }

                    manager.joinLobby(username);
                }
                manager.displayLobby();
                break;
            }

            case 3: {
                cout << "\n--- [3] PROCESS MATCHMAKING ---\n";
                manager.processMatchmaking();
                break;
            }

            case 4:{
                int winner = 0;
                cout << "\n--- [4] RECORD MATCH OUTCOME ---\n";
                if (!manager.displayCurrentMatch()) {
                    break;
                }

                cout << "Enter winner [1 or 2]: ";
                if (!(cin >> winner)) {
                    cout << "  [ERROR] Invalid entry. Please enter a number.\n";
                    clearInputBuffer();
                    break;
                }

                manager.recordResult(winner);
                break;
            }

            case 5: {
                cout << "\n--- [5] UNDO LAST MATCH RESULT ---\n";
                manager.undoLastResult();
                break;
            }

            case 6:{
                cout << "\n--- [6] LIVE LEADERBOARD ---\n";
                manager.displayLeaderboard();
                break;
            }

            case 7: {
                int low = 0;
                int high = 0;
                cout << "\n--- [7] QUERY RATING RANGE ---\n";

                cout << "Enter lowest rating: ";
                if (!(cin >> low)) {
                    cout << "  [ERROR] Invalid entry. Please enter a number.\n";
                    clearInputBuffer();
                    break;
                }

                cout << "Enter highest rating: ";
                if (!(cin >> high)) {
                    cout << "  [ERROR] Invalid entry. Please enter a number.\n";
                    clearInputBuffer();
                    break;
                }

                manager.displayRange(low, high);
                break;
            }

            case 8: {
                string username;
                cout << "\n--- [8] LOOKUP PLAYER PROFILE ---\n";
                cout << "Enter username: ";
                cin >> username;

                manager.lookupPlayer(username);
                break;
            }

            case 9:
                cout << "\nExiting application. Goodbye!\n";
                return 0;

            default:
                cout << "  ERROR: Option out of range. Select between 1 and 9.\n";
                break;
        }
    }

    return 0;
}