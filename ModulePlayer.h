#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

enum PlayerState
{
	IDLE = 0,
	WALK_FORDWARD,
	WALK_BACKWARD,
	KICK,
	PUNCH,
	JUMP_UP,
	JUMP_MID_AIR,
	JUMP_DOWN
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:



	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation backward;
	Animation forward;
	Animation kick;
	Animation punch;
	Animation jumpUp;
	Animation jumpDown;
	Animation jumpMidAir;
	iPoint position;

	int minPosition = 0;
	int maxPosition = 720;

	PlayerState currentState = IDLE;
};

#endif // __MODULEPLAYER_H__