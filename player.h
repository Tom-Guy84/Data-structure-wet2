//
// Created by Tom Guy on 01/02/2022.
//

#include <ostream>

#ifndef DAST_PLAYER_H
#define DAST_PLAYER_H

namespace wet2_dast {

    class Player {
    private:
        int player_id;
        int level;
        int group;
        bool sort_by_score;
        int score;
    public:
        Player(int player_id, int level, int group, bool sort_by_score, int score);//
        ~Player() = default;
        Player()=default;
        Player(const Player &p) = default;
        Player& operator=(const Player& p);
        int getGroup() const;
        void setLevel(int level_to_set);// p->level_to_set=level_to_set.
        int getLevel() const;
        int getId() const;
        void setScore(int score_to_add);
        int getScore() const;
        void setGroup(int group);
        bool operator==(const Player &p1) const;
        bool operator<=(const Player& other) const;
        Player* createPlayerByLevel() const;
    };


}//namespace wet2_dast


#endif //DAST_PLAYER_H
