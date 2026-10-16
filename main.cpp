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
        cout << "  2. Join Matchmaking Lobby Queue     (Disabled)\n";
        cout << "  3. Process Matchmaking              (Disabled)\n";
        cout << "  4. Record Match Outcome             (Disabled)\n";
        cout << "  5. Undo Last Match Result           (Disabled)\n";
        cout << "  6. Display Live Leaderboard         (Disabled)\n";
        cout << "  7. Query Rating Range               (Disabled)\n";
        cout << "  8. Lookup Player Profile & History  (Disabled)\n";
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
                cout << "Enter username (1-16 chars): ";
                cin >> username;

                manager.registerPlayer(username);
                break;
            }

            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                cout << "\n  [INFO] Feature currently disabled for testing Option 1.\n";
                break;

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