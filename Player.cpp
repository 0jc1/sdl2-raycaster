#include "Player.hpp"

Player::Player(double posX, double posY, double dirX, double dirY) {
    this->pos.x = posX;
    this->pos.y = posY;
    this->dir.x = dirX;
    this->dir.y = dirY;

    plane.x = 0, plane.y = 0.66;
}
