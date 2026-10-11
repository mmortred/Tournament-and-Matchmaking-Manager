#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>
#include <string>

struct MatchUndoRecord {
    int match_id;
    std::string winner;
    std::string loser;

    int winnerPrevRating;
    int winnerPrevWins;

    int loserPrevRating;
    int loserPrevLosses;

    MatchUndoRecord(int match_id, const std::string& winner = "", const std::string& loser = "",
                    int w_rating = 0, int w_wins = 0,
                    int l_rating = 0, int l_loses = 0)
        : match_id(match_id),
          winner(winner),
          loser(loser),
          winnerPrevRating(w_rating),
          winnerPrevWins(w_wins),
          loserPrevRating(l_rating),
          loserPrevLosses(l_loses) {}
};

#endif