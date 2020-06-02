//
// Created by qt on 11.05.2020.
//

#ifndef TIN_PLAYERMODEL_H
#define TIN_PLAYERMODEL_H

struct PlayerModel {
    int id;
    int points;

    bool is_enemy;
    double pos_x, pos_y;

    PlayerModel(int id_, int points_, double pos_x_, double pos_y_):
        id(id_), points(points_), is_enemy(true), pos_x(pos_x_), pos_y(pos_y_) {};
};


#endif //TIN_PLAYERMODEL_H
