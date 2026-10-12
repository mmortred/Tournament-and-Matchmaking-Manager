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
    TournamentManager manager;
    int choice = 0;

    cout << "\n=======================================================\n";
    cout << "     WELCOME TO TOURNAMENT MATCHMAKING MANAGER         \n";
    cout << "                 (SRS v1.2 CLI Engine)                 \n";
    cout << "=======================================================\n";

    while (true) {
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
            continue;
        }

        switch (choice) {
            case 1: {
                string username;
                cout << "\n--- [1] REGISTER NEW PLAYER ---\n";
                cout << "Enter username (1-16 chars): ";
                cin >> username;
                manager.registerPlayer(username);
                break;
            }

            case 2: {
                string username;
                cout << "\n--- [2] JOIN LOBBY QUEUE ---\n";
                cout << "Enter registered username: ";
                cin >> username;
                manager.joinLobby(username);
                break;
            }

            case 3: {
                cout << "\n--- [3] PROCESS MATCHMAKING ---\n";
                Player* p1 = nullptr;
                Player* p2 = nullptr;

                if (manager.processMatchmaking(&p1, &p2)) {
                    cout << "\nWould you like to record this match result now? (1: Yes, 0: Later): ";
                    int recordNow = 0;
                    if (cin >> recordNow && recordNow == 1) {
                        cout << "\nSelect Winner:\n";
                        cout << "  1. " << p1->username << "\n";
                        cout << "  2. " << p2->username << "\n";
                        cout << "Choice [1/2]: ";
                        int winnerChoice = 0;
                        cin >> winnerChoice;

                        if (winnerChoice == 1) {
                            manager.recordResult(p1->username, p2->username);
                        } else if (winnerChoice == 2) {
                            manager.recordResult(p2->username, p1->username);
                        } else {
                            cout << "  [INFO] Invalid choice. Result recording skipped.\n";
                        }
                    }
                }
                break;
            }

            case 4: {
                string winner, loser;
                cout << "\n--- [4] RECORD MATCH OUTCOME ---\n";
                cout << "Enter Winner username: ";
                cin >> winner;
                cout << "Enter Loser username:  ";
                cin >> loser;
                manager.recordResult(winner, loser);
                break;
            }

            case 5: {
                cout << "\n--- [5] UNDO LAST RESULT ---\n";
                manager.undoLastResult();
                break;
            }

            case 6: {
                manager.printLeaderboard();
                break;
            }

            case 7: {
                int minRating = 0, maxRating = 0;
                cout << "\n--- [7] RATING RANGE QUERY ---\n";
                cout << "Enter minimum rating: ";
                if (!(cin >> minRating)) {
                    clearInputBuffer();
                    break;
                }
                cout << "Enter maximum rating: ";
                if (!(cin >> maxRating)) {
                    clearInputBuffer();
                    break;
                }
                manager.printRange(minRating, maxRating);
                break;
            }

            case 8: {
                string username;
                cout << "\n--- [8] LOOKUP PLAYER PROFILE ---\n";
                cout << "Enter username to lookup: ";
                cin >> username;
                manager.lookupPlayer(username);
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

    return 0;
}