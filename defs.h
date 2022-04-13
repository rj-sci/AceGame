#pragma once

	enum Name {player = 0, enemy = 1, bullet = 2, fireball = 3, powerup = 4, missile = 5, asteroid = 6};
	//enum Name { UFO, alien, player, satellite, bullet, asteroid, tile, powerup, shield};
	enum PUpType {None = 0, shield_type = 1, satellite_type = 2};

#define MAX_SHIELD 10.0
#define PLAYER_BULLET_TIME 2.0f
#define ENEMY_BULLET_TIME 7.0f
#define MAX_BULLET_SPEED 2.0f
#define ASTEROID_LIFE_TIME 7.0f
#define HIT_COOLDOWN 0.5
	
