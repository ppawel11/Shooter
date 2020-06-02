//
// Created by pawel on 31.05.2020.
//

#ifndef TIN_BULLETMODEL_H
#define TIN_BULLETMODEL_H

struct BulletModel {
    double pos_x, pos_y;

    BulletModel(double pos_x_, double pos_y_):
            pos_x(pos_x_), pos_y(pos_y_) {};
};
#endif //TIN_BULLETMODEL_H
