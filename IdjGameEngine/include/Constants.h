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
		const int INITIAL_HP = 50;
		const int LINEAR_SPEED = 150;
		const int ROTATION_SPEED = 10;
		const int DEATH_FRAME_COUNT = 4;
		const float DEATH_FRAME_TIME = 0.1f;
		const float DEATH_SECONDS_TO_SELF_DESTRUCT = 0.4f;
	}

	namespace PenguinBody {
		const int INITIAL_POSITION_X = 704;
		const int INITIAL_POSITION_Y = 640;
		const int INITIAL_HP = 40;
		const int LINEAR_SPEED_INCREMENT = 10;
		const int MAX_LINEAR_SPEED = 150;
		const int ANGULAR_SPEED = 1;
		const int DEATH_FRAME_COUNT = 5;
		const float DEATH_FRAME_TIME = 0.1f;
		const float DEATH_SECONDS_TO_SELF_DESTRUCT = 0.5f;
	}

	namespace PenguinCannon {
		const float BULLET_SPEED = 200;
		const int BULLET_DAMAGE = 10;
		const float BULLET_MAX_DISTANCE = 2000;
		const float COOLDOWN_TIME = 0.5;
	}

	namespace Bullet {
		const int FRAME_COUNT = 3;
		const float FRAME_TIME = 0.5;
	}

	namespace Minion {
		const float BULLET_SPEED = 200;
		const int BULLET_DAMAGE = 10;
		const float BULLET_MAX_DISTANCE = 2000;
		const float ANGULAR_VELOCITY = 0.15707963267f;
	}

	namespace Camera {
		const int SPEED = 100;
	}

}
