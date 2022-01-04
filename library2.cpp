
#include "PlayerManager.h"
#include "library2.h"
using namespace wet2_dast;

void *Init(int k, int scale) {

    PlayerManager *DS;
    DS->PlayerManagerInit(k, scale);
    if (!DS) {
        return NULL;
    }
    return (void *) DS;
}

StatusType MergeGroups(void *DS, int GroupID1, int GroupID2) {
    auto *DS_OK = (PlayerManager *) DS;
    return DS_OK->mergeGroups(GroupID1, GroupID2);

}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score) {
    auto *DS_OK = (PlayerManager *) DS;
    return DS_OK->addPlayer(PlayerID, GroupID, score);
}

StatusType RemovePlayer(void *DS, int PlayerID) {
    auto *DS_OK = (PlayerManager *) DS;
    return DS_OK->removePlayer(PlayerID);
}

StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease) {
    auto *DS_OK = (PlayerManager *) DS;
    return DS_OK->increasePlayerIDLevel(PlayerID, LevelIncrease);
}

StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore) {
    auto *DS_OK = (PlayerManager *) DS;
    return DS_OK->changePlayerIDScore(PlayerID, NewScore);
}

StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel, int higherLevel,
                                                double *players) {
    auto *DS_OK = (PlayerManager *) DS;
    return DS_OK->getPercentOfPlayersWithScoreInBounds(GroupID, score, lowerLevel, higherLevel, players);
}

StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double *level) {
    auto *DS_OK = (PlayerManager *) DS;
    return DS_OK->averageHighestPlayerLevelByGroup(GroupID, m, level);
}

    StatusType
    GetPlayersBound(void *DS, int GroupID, int score, int m, int *LowerBoundPlayers, int *HigherBoundPlayers) {
        auto *DS_OK = (PlayerManager *) DS;
        return DS_OK->getPlayersBound(GroupID, score, m, LowerBoundPlayers, HigherBoundPlayers);
    }
void Quit(void **DS) {
    auto DS_OK = (PlayerManager *) *DS;
    if (!DS) {
        return;
    }
    delete DS_OK;
    * DS = NULL;

}