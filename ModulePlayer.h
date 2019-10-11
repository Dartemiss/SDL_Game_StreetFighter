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
	WALK_BACKWARD
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
	iPoint position;

	PlayerState currentState = IDLE;
};

#endif // __MODULEPLAYER_H__