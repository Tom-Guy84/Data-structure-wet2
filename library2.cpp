
#include "PlayerManager.h"
#include "library2.h"
//what i want- i want to sum on all averages on tree.
//how do i do it. I need to go on a tree of all players ,
using namespace wet2_dast;

void *Init(int k, int scale) {
    if (k <= 0 || scale <= 0 || scale > 200)
        return NULL;
    try {
        auto *manager = PlayerManager::Init(k, scale);
        return (void *) manager;
    }
    catch (std::exception &e) {
        return NULL;//hello
    }
}

StatusType MergeGroups(void *DS, int GroupID1, int GroupID2) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }

    auto *DS_OK = (PlayerManager *) DS;
    return DS_OK->mergeGroups(GroupID1, GroupID2);

}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    auto *DS_OK = (PlayerManager *) DS;
    return DS_OK->addPlayer(PlayerID, GroupID, score);
}

StatusType RemovePlayer(void *DS, int PlayerID) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    auto *DS_OK = (PlayerManager *) DS;
    return DS_OK->removePlayer(PlayerID);
}

StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    auto *DS_OK = (PlayerManager *) DS;
    return DS_OK->increasePlayerIDLevel(PlayerID, LevelIncrease);
}

StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    auto *DS_OK = (PlayerManager *) DS;
    return DS_OK->changePlayerIDScore(PlayerID, NewScore);
}

StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel, int higherLevel,
                                                double *players) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    auto *DS_OK = (PlayerManager *) DS;
    return DS_OK->getPercentOfPlayersWithScoreInBounds(GroupID, score, lowerLevel, higherLevel, players);
}

StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double *level) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    auto *DS_OK = (PlayerManager *) DS;
    return DS_OK->averageHighestPlayerLevelByGroup(GroupID, m, level);
}

StatusType
GetPlayersBound(void *DS, int GroupID, int score, int m, int *LowerBoundPlayers, int *HigherBoundPlayers) {
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    auto *DS_OK = (PlayerManager *) DS;
    return DS_OK->getPlayersBound(GroupID, score, m, LowerBoundPlayers, HigherBoundPlayers);
}

void Quit(void **DS) {

    if (!DS) {
        return;
    }
    delete (PlayerManager *) *DS;
    *DS = NULL;

}
