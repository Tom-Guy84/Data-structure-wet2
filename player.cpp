#include <iostream>
#include "player.h"

namespace wet2_dast
{

    Player::Player(int player_id, int level, int group = 0, bool sort_by_score = true, int score=0) :
            group(group), sort_by_score(sort_by_score), score(score)
    {
        this->player_id = player_id;
        this->level = level;
    }

    void Player::setLevel(int level_to_set)
    {
        level += level_to_set; //tested
    }

    int Player::getLevel() const
    {
        return level; //tested
    }

    bool Player::operator==(const Player &p1) const
    {
        return (player_id == p1.player_id);
    }

    int Player::getId() const
    {
        return player_id;
    }


    void Player::setGroup(int group_to_set)
    {
        group = group_to_set;
    }


    bool Player::operator<=(const Player &other) const
    {
        if (!sort_by_score)
        {
            return (level < other.level) || (level == other.level && player_id < other.player_id);
        } //else, sort by score first
        return ((score < other.score) || (score == other.score && level < other.level)
                    || (score == other.score && level == other.level && player_id < other.player_id));
    }

    int Player::getGroup() const {
        return group;
    }

    Player *Player::createPlayerByLevel() const
    {
        auto* playerByLevel  = new Player(player_id, level, group, false, score);
        return playerByLevel;
    }

    Player &Player::operator=(const Player &p)
    {
        player_id = p.player_id;
        level = p.level;
        group = p.group;
        sort_by_score = p.sort_by_score;
        score = p.score;
        return *this;
    }

    void Player::setScore(int score_to_add)
    {
        score = score_to_add;
    }

    int Player::getScore() const
    {
        return score;
    }


} //namespace wet2_dast
