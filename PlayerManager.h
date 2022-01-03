//
// Created by proje on 02/01/2022.
//
#include <iostream>
#include "group.h"
#include "AVLRankTree.h"
#include "player.h"
#include "library2.h"
#include "HashTable.h"
#include "Union-Find.h"

#ifndef WET2_PLAYERMANAGER_H
#define WET2_PLAYERMANAGER_H

namespace wet2_dast {
    class PlayerManager
    {
        int num_of_groups;
        int scale;
        Union_Find<Group>* groups;
        PlayerManager(int k, int scale);
    public:
        PlayerManager *PlayerManagerInit(int k, int scale);

        StatusType mergeGroups(int GroupID1, int GroupID2);
        StatusType addPlayer(int PlayerID, int GroupID, int score);
        StatusType removePlayer(int PlayerID);
        StatusType increasePlayerIDLevel(int PlayerID, int LevelIncrease);
        StatusType changePlayerIDScore(int PlayerID, int NewScore);
        StatusType getPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel,
                                                        int higherLevel, double* average);
        StatusType averageHighestPlayerLevelByGroup(int GroupID, int m, double* avgLevel);
        StatusType getPlayersBound(int GroupID, int score, int m, int * LowerBoundPlayers, int *HigherBoundPlayers);
        ~PlayerManager() = default;
    };
} //namespace wet2_dast

#endif //WET2_PLAYERMANAGER_H
