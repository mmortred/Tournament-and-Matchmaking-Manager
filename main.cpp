#include <iostream>
using namespace std;

/*

tournament-manager/
├── Player.hpp            (Player struct & MatchRecord)
├── Queue.hpp             (Doubly-Linked Queue ADT)
├── Stack.hpp             (Undo Stack ADT)
├── LinkedList.hpp        (Match History ADT)
├── HashTable.hpp        (Player Lookup ADT)
├── BST.hpp               (Leaderboard ADT)
├── TournamentManager.hpp (System Orchestrator)
└── main.cpp              (Console CLI Driver)


[1. Player.hpp] ───> [2. LinkedList.hpp]
             │                     │
             ├─────────────────────┴──────────────┐
             ▼                                    ▼
  [3. Queue.hpp] & [4. Stack.hpp]      [5. HashTable.hpp]
             │                                    │
             └──────────────────┬─────────────────┘
                                ▼
                         [6. BST.hpp]
                                │
                                ▼
                   [7. TournamentManager.hpp]
                                │
                                ▼
                          [8. main.cpp]

*/
int main() {
    int option = 0;

    cout << "╔═════════════════════════════════════════════╗\n";
    cout << "║         TOURNAMENT MATCHMAKING MANAGER      ║\n";
    cout << "╚═════════════════════════════════════════════╝\n";


        cout << "\n  [1] Register New Player\n";
        cout << "  [2] Join Lobby Queue\n";
        cout << "  [3] Process Matchmaking\n";
        cout << "  [4] Undo Last Match Result\n";
        cout << "  [5] Display Live Leaderboard\n";
        cout << "  [6] Query Rating Range\n";
        cout << "  [7] Lookup Player Profile & History\n";
        cout << "  [8] Exit\n\n";
        cout << "  Select Option > ";

    

    return 0;
}