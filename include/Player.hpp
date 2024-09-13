#include "Vector2.hpp"

class Player {
    public:
        Player(double pX, double pY, double dX, double dY);
        Vector2 pos;
        Vector2 dir;
        Vector2 plane;

        double walkSpeed = 0.1;
        double rotSpeed = 0.04;

    private:
        double playerHeight;
};