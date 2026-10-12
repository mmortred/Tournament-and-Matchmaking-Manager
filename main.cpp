#include <iostream>
#include <string>

// Include system orchestrator header
#include "TournamentManager.hpp"

using namespace std; // Safe to use inside .cpp files!

// Simple input clearing function without <limits>
void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n'); // Discard invalid characters up to Enter
}

int main() {
    // TournamentManager manager;
    int choice = 0;

    cout << "\n=======================================================\n";
    cout << "     WELCOME TO TOURNAMENT MATCHMAKING MANAGER         \n";
    cout << "=======================================================\n";

        cout << "\n------------------ ADMIN CONSOLE MENU ------------------\n";
        cout << "  1. Register New Player              (Hash Table + BST)\n";
        cout << "  2. Join Matchmaking Lobby Queue     (Queue ADT)\n";
        cout << "  3. Process Matchmaking              (Single-Pass Search)\n";
        cout << "  4. Record Match Outcome             (BST + LinkedList)\n";
        cout << "  5. Undo Last Match Result           (Stack Engine)\n";
        cout << "  6. Display Live Leaderboard         (In-Order BST)\n";
        cout << "  7. Query Rating Range               (BST Range Search)\n";
        cout << "  8. Lookup Player Profile & History  (HashTable + List)\n";
        cout << "  9. Exit System\n";
        cout << "--------------------------------------------------------\n";
        cout << "Select Option [1-9]: ";

        if (!(cin >> choice)) {
            cout << "  [ERROR] Invalid entry. Please enter a number between 1 and 9.\n";
            clearInputBuffer();
        }

        switch (choice) {
            case 1: {
                string username;
                cout << "\n--- [1] REGISTER NEW PLAYER ---\n";
                cout << "Enter username (1-16 chars): ";
                cin >> username;
                break;
            }

            case 2: {
                string username;
                cout << "\n--- [2] JOIN LOBBY QUEUE ---\n";
                cout << "Enter registered username: ";
                cin >> username;
                break;
            }

            case 3: {
                cout << "\n--- [3] PROCESS MATCHMAKING ---\n";
                break;
            }

            case 4: {
                string winner, loser;
                cout << "\n--- [4] RECORD MATCH OUTCOME ---\n";
                cout << "Enter Winner username: ";
                cin >> winner;
                cout << "Enter Loser username:  ";
                cin >> loser;
                break;
            }

            case 5: {
                cout << "\n--- [5] UNDO LAST RESULT ---\n";
                break;
            }

            case 6: {
                break;
            }

            case 7: {
                int minRating = 0, maxRating = 0;
                cout << "\n--- [7] RATING RANGE QUERY ---\n";
                cout << "Enter minimum rating: ";
                break;
            }

            case 8: {
                string username;
                cout << "\n--- [8] LOOKUP PLAYER PROFILE ---\n";
                cout << "Enter username to lookup: ";
                cin >> username;
                break;
            }

            case 9: {
                cout << "\nExiting application. All memory deallocated cleanly. Goodbye!\n";
                return 0;
            }

            default: {
                cout << "  [ERROR] Option out of range. Please select between 1 and 9.\n";
                break;
            }
        }
    }

