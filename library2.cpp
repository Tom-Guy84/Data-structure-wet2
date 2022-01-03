
#include "PlayerManager.h"
#include "library2.h"
using namespace wet2_dast;

    void *Init(int k, int scale) {
        PlayerManager *DS = new PlayerManager();
        if (!DS) {
            return NULL ;
        }
        return (void *) DS;
    }

    StatusType MergeGroups(void *DS, int GroupID1, int GroupID2) {
        return FAILURE;
    }

    StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score) {
        return FAILURE;
    }

    StatusType RemovePlayer(void *DS, int PlayerID) {
        return FAILURE;
    }

    StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease) {
        return FAILURE;
    }

    StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore) {
        return FAILURE;
    }

    StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel, int higherLevel,
                                                    double *players) {
        return FAILURE;
    }

    StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double *level) {
        return FAILURE;
    }

    StatusType
    GetPlayersBound(void *DS, int GroupID, int score, int m, int *LowerBoundPlayers, int *HigherBoundPlayers) {
        return FAILURE;
    }

    void Quit(void **DS) {

    }
