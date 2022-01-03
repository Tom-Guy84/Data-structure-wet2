
#include "group.h"
#include "player.h"

namespace wet2_dast {

    bool Group::operator==(const Group &group) const {
        return (this->Group_Id == group.Group_Id);
    }

    void merge(Group* to_delete,Group *to_insert) //to_delete is deleted
    {
        if (to_delete->size == 0)
            return;
        combineTrees(to_delete->players_by_level, to_insert->players_by_level);//combine two trees
        combineTrees(to_delete->players_by_score, to_insert->players_by_score);//combine two tress
        to_insert->size+=to_delete->size;
        Player **players_level = to_insert->players_by_level.inorderOut(to_insert->players_by_level.getSize());
        Player **players_id = to_insert->players_by_score.inorderOut(to_insert->players_by_score.getSize());
        for(int i=0; i < to_insert->size; i++)
        {
            players_id[i]->setGroup(to_insert->Group_Id);
        }
        to_insert->players_by_score.inorderInsert(players_id ,to_insert->size+to_delete->size);
        to_insert->players_by_level.inorderInsert(players_level,to_insert->size+to_delete->size);
        delete[] players_level;
        delete[] players_id;
        to_delete->size = 0;
        Union(to_insert->players, to_delete->players);
    }


    int Group::GetSize() const {
        return players_by_level.getSize(); // should be return Players(the tree)->size;
    }


    void Group::AddPlayer(Player& player) {
        players.insert_object(&player, player.getId());
        size++;
    }

    Group::Group(int Group_id) : Group_Id(Group_id), players_by_score(),
                                 players_by_level(), size(0), players()  {
        if (Group_id <= 0) {
            throw;
        }
    }

    Group::Group() {
        Group_Id = 0;
        size = 0;
    }

    bool Group::operator<=(const Group &other) const {
        return Group_Id < other.Group_Id;
    }

    Player* Group::findPlayer(int PlayerId) {
        return players.find_object(PlayerId);
    }

    void Group::removePlayer(int player_id) {
        Player* player = players.find_object(player_id);
        if(!player)
            throw std::exception();
        size--;
        if(player->getLevel() == 0)
        {
            players.delete_object(player_id);
            return;
        }
        Player* player_by_level = player->createPlayerByLevel();
        players_by_level.remove(*player_by_level);
        players_by_score.remove(*player);
        players.delete_object(player_id);
        delete player_by_level;
    }

    void Group::increaseLevelToPlayer(int player_id, int levelIncrease)
    {
        Player* player = players.find_object(player_id);
        if(player->getLevel() == 0)
        {
            player->setLevel(levelIncrease);
            auto* player_by_score = new Player(*player);
            players_by_score.insert(*player_by_score);
            Player* player_by_level = player->createPlayerByLevel();
            players_by_level.insert(*player_by_level);
            return;
        }
        Player* player_by_level = player->createPlayerByLevel();//to find the player.
        players_by_level.remove(*player_by_level);
        player_by_level->setLevel(levelIncrease);
        players_by_level.insert(*player_by_level);
        players_by_score.remove(*player);
        player->setLevel(levelIncrease);
        auto* player_by_score = new Player(*player);
        players_by_score.insert(*player_by_score);
    }

    Player** Group::getPlayersByLevel()
    {
        return players_by_level.inorderOut(players_by_level.getSize());
    }

    void Group::increaseScoreToPlayer(int player_id, int scoreIncrease)
    {
        Player* player = players.find_object(player_id);
        if(!player)
            throw std::exception();
        players_by_score.remove(*player);
        player->setScore(scoreIncrease);
        Player* player_by_score = new Player(*player);
        players_by_score.insert(*player_by_score);
    }

} //namespace wet2_dast

