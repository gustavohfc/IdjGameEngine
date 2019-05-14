#pragma once

namespace Constants {

    namespace Game {
        const int WINDOW_WIDTH = 1024;
        const int WINDOW_HEIGHT = 600;
        const std::string WINDOW_TITLE = "Gustavo Henrique Fernandes Carvalho 14/0021671";
        const int SDL_DELAY = 33; //ms
    }
    
    namespace TileMap {
        const float PARALLAX_LAYER_OFFSET = 0.5;
    }

    namespace TileSet {
        const int TILE_WIDTH = 64;
        const int TILE_HEIGHT = 64;
    }

    namespace Alien {
        const int NUMBER_OF_MINIONS = 5;
        const int INITIAL_POSITION_X = 512;
        const int INITIAL_POSITION_Y = 300;
    }

    namespace PenguinBody {
        const int INITIAL_POSITION_X = 704;
        const int INITIAL_POSITION_Y = 640;
        const int INITIAL_HP = 40;
        const int LINEAR_SPEED_INCREMENT = 10;
        const int MAX_LINEAR_SPEED = 200;
        const int ANGULAR_SPEED = 1;
    }

    namespace PenguinCannon {
        const int BULLET_SPEED = 100;
        const int BULLET_DAMAGE = 10;
        const int BULLET_MAX_DISTANCE = 1000;
        const float COOLDOWN_TIME = 0.5;
    }

    namespace Bullet {
        const int FRAME_COUNT = 3;
        const int FRAME_TIME = 1;
    }

    namespace Minion {
        const int BULLET_SPEED = 100;
        const int BULLET_DAMAGE = 10;
        const int BULLET_MAX_DISTANCE = 1000;
        const float ANGULAR_VELOCITY = 0.15707963267;
    }

    namespace Camera {
        const int SPEED = 100;
    }

}
