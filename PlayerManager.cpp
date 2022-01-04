//
// Created by proje on 02/01/2022.
//

#include "PlayerManager.h"
namespace wet2_dast{
    PlayerManager::PlayerManager(int k, int scale)
    {
        num_of_groups = k;
        this->scale = scale;
        groups = new Union_Find<Group>(k+1); //time complexity is O(k+1) because the function creates
                                                 // all the groups in the structure
    }

    StatusType PlayerManager::mergeGroups(int GroupID1, int GroupID2)
    {
        if(GroupID1 <=0 || GroupID1 > num_of_groups || GroupID2 <= 0 || GroupID2 > num_of_groups)
        {
            return INVALID_INPUT;
        }
        try
        {
            groups->Union(GroupID1, GroupID2);
            return SUCCESS;
        }
        catch (std::exception& e)
        {
            return ALLOCATION_ERROR;
        }
    }

    StatusType PlayerManager::addPlayer(int PlayerID, int GroupID, int score)
    {
        if(PlayerID <= 0 || GroupID <= 0 || GroupID > num_of_groups || score <=0 || score > scale)
            return INVALID_INPUT;
        try
        {
            auto *player_in_group = new Player(PlayerID, 0, GroupID, true, score);
            Group *players_group = groups->find(GroupID);
            players_group->AddPlayer(*player_in_group);
            auto *player = new Player(PlayerID, 0, GroupID, true, score);
            Group *group = groups->find(0);
            group->AddPlayer(*player);
            return SUCCESS;
        }
        catch (HashTable<Player>::exceptions& e)
        {
            return FAILURE;
        }
        catch (std::exception& e)
        {
            return ALLOCATION_ERROR;
        }
    }

    StatusType PlayerManager::removePlayer(int PlayerID)
    {
        if(PlayerID <= 0)
            return INVALID_INPUT;
        try
        {
            Group* group = groups->find(0);
            Player* player = group->findPlayer(PlayerID);
            int GroupID = player->getGroup();
            Group *players_group = groups->find(GroupID);
            players_group->removePlayer(PlayerID);
            group->removePlayer(PlayerID);
        }
        catch (std::exception &e) {
            return FAILURE;
        }
    }

    StatusType
    PlayerManager::getPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel,
                                                        double *average) {
        return FAILURE;
    }

    StatusType PlayerManager::increasePlayerIDLevel(int PlayerID, int LevelIncrease) {
        return FAILURE;
    }

    StatusType PlayerManager::changePlayerIDScore(int PlayerID, int NewScore) {
        return FAILURE;
    }

    StatusType PlayerManager::averageHighestPlayerLevelByGroup(int GroupID, int m, double *avgLevel) {
        return FAILURE;
    }

    StatusType
    PlayerManager::getPlayersBound(int GroupID, int score, int m, int *LowerBoundPlayers, int *HigherBoundPlayers) {
        return FAILURE;
    }

    PlayerManager::~PlayerManager() {
        delete groups;

    }


} //namespace wet2_dast