//
// Created by Tom Guy on 01/02/2022.
//

#include "AVLRankTree.h"
#include "HashTable.h"

#ifndef DAST_GROUP_H
#define DAST_GROUP_H

namespace wet2_dast {
    class Player;
    class Group {
    private:
        int Group_Id;
        AVLRankTree<Player> players_by_score;
        AVLRankTree<Player> players_by_level;
        HashTable<Player> players;
        int* scores;
        int size;
    public:
        explicit Group(int Group_id);
        Group();
        ~Group();
        Group(const Group &group) =delete;
        Group& operator=(const Group &other)=delete ;
        bool operator==(const Group &group) const;
        int GetSize() const;
        bool operator<=(const Group& other) const;
        friend void merge(Group* to_delete,Group *to_insert);
        void AddPlayer(Player& player);
        Player* findPlayer(int PlayerId);
        void removePlayer(int player_id);
        void increaseLevelToPlayer(int player_id, int levelIncrease);
        void increaseScoreToPlayer(int player_id, int scoreIncrease);
//        Player ** getPlayersByLevel();
        double getPercentOfPlayersWithScoreInBounds(int score, int lowerLevel, int higherLevel) const;
        double averageHighestPlayerLevel(int wanted_number_of_players) const;
    class exceptions : public std::exception{};
    };


//
} //namespace wet2_dast
#endif //DAST_GROUP_H
