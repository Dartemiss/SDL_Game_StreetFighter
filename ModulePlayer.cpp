#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "assert.h"
#include<iostream>
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 100;
	position.y = 125;

	// idle animation (arcade sprite sheet)
	idle.frames.push_back({7, 14, 60, 90});
	idle.frames.push_back({95, 15, 60, 89});
	idle.frames.push_back({184, 14, 60, 90});
	idle.frames.push_back({276, 11, 60, 93});
	idle.frames.push_back({366, 12, 60, 92});
	idle.speed = 0.1f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 128, 58, 91});
	backward.frames.push_back({974, 129, 57, 89});
	backward.speed = 0.1f;

	// TODO 8: setup the walk forward animation from ryu4.png
	forward.frames.push_back({ 7, 127, 61, 93 });
	forward.frames.push_back({ 78, 127, 61, 93 });
	forward.frames.push_back({ 162, 127, 66, 93 });
	forward.frames.push_back({ 258, 127, 65, 93 });
	forward.frames.push_back({ 352, 127, 61, 93 });
	forward.frames.push_back({ 432, 127, 61, 93 });
	forward.speed = 0.1f;


	//Kick
	kick.frames.push_back({ 588, 267, 90, 95 });
	kick.frames.push_back({ 678, 266, 98, 94 });
	kick.frames.push_back({ 777, 265, 113, 94 });
	kick.frames.push_back({ 678, 266, 98, 94 });
	kick.speed = 0.15f;

	//punch
	punch.frames.push_back({ 244, 268, 80, 94 });
	punch.frames.push_back({ 332, 268, 88, 94 });
	punch.frames.push_back({ 431, 268, 108, 94 });
	punch.frames.push_back({ 332, 268, 88, 94 });
	punch.speed = 0.15f;

	//jump
	jumpUp.frames.push_back({15,844,65,94});
	jumpUp.frames.push_back({ 95,820,62,114 });
	jumpUp.frames.push_back({170,798,59,100});
	jumpMidAir.frames.push_back({246,792,60,92});
	jumpDown.frames.push_back({323,810,56,78});
	jumpDown.frames.push_back({395,800,54,102});
	jumpDown.frames.push_back({461,813,64,119});
	jumpUp.speed = 0.125f;
	jumpMidAir.speed = 0.125f;
	jumpDown.speed = 0.125f;
}


ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ryu4.png"); // arcade version

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update()
{
	Animation* currentAnimation = nullptr;
	// TODO 9: Draw the player with its animation
	switch (currentState)
	{
	case IDLE:
		if(App->input->GetKey(SDL_SCANCODE_D))
		{
			currentState = WALK_FORDWARD;
			currentAnimation = &forward;
			++position.x;
		}
		else if(App->input->GetKey(SDL_SCANCODE_A))
		{
			currentState = WALK_BACKWARD;
			currentAnimation = &backward;
			--position.x;
		}
		else if(App->input->GetKey(SDL_SCANCODE_F))
		{
			currentState = KICK;
			currentAnimation = &kick;
		}
		else if(App->input->GetKey(SDL_SCANCODE_G))
		{
			currentState = PUNCH;
			currentAnimation = &punch;

		}
		else if(App->input->GetKey(SDL_SCANCODE_J))
		{
			currentState = JUMP_UP;
			currentAnimation = &jumpUp;
		}
		else
		{
			currentState = IDLE;
			currentAnimation = &idle;
		}
		
		break;
	case WALK_FORDWARD:
		if(App->input->GetKey(SDL_SCANCODE_A))
		{
			currentState = WALK_BACKWARD;
			currentAnimation = &backward;
			--position.x;
		}
		else if(App->input->GetKey(SDL_SCANCODE_D))
		{
			currentState = WALK_FORDWARD;
			currentAnimation = &forward;
			++position.x;
		}
		else if (App->input->GetKey(SDL_SCANCODE_F))
		{
			currentState = KICK;
			currentAnimation = &kick;
		}
		else if (App->input->GetKey(SDL_SCANCODE_G))
		{
			currentState = PUNCH;
			currentAnimation = &punch;

		}
		else if (App->input->GetKey(SDL_SCANCODE_J))
		{
			currentState = JUMP_UP;
			currentAnimation = &jumpUp;
		}
		else
		{
			currentState = IDLE;
			currentAnimation = &idle;
		}
		break;
	case WALK_BACKWARD:
		if (App->input->GetKey(SDL_SCANCODE_A))
		{
			currentState = WALK_BACKWARD;
			currentAnimation = &backward;
			--position.x;

		}
		else if (App->input->GetKey(SDL_SCANCODE_D))
		{
			currentState = WALK_FORDWARD;
			currentAnimation = &forward;
			++position.x;
		}
		else if (App->input->GetKey(SDL_SCANCODE_F))
		{
			currentState = KICK;
			currentAnimation = &kick;
		}
		else if (App->input->GetKey(SDL_SCANCODE_G))
		{
			currentState = PUNCH;
			currentAnimation = &punch;

		}
		else if (App->input->GetKey(SDL_SCANCODE_J))
		{
			currentState = JUMP_UP;
			currentAnimation = &jumpUp;
		}
		else
		{
			currentState = IDLE;
			currentAnimation = &idle;
		}
		break;
	case KICK:
		if(kick.isLastFrame)
		{
			//Continue Animation
			currentState = IDLE;
			currentAnimation = &idle;
		}
		else
		{
			currentState = KICK;
			currentAnimation = &kick;
		}
		break;

	case PUNCH:
		if(punch.isLastFrame)
		{
			//Continue Animation
			currentState = IDLE;
			currentAnimation = &idle;
		}
		else
		{
			currentState = PUNCH;
			currentAnimation = &punch;
		}
		break;

	case JUMP_UP:
		if(jumpUp.isLastFrame)
		{
			currentState = JUMP_MID_AIR;
			currentAnimation = &jumpMidAir;
		}
		else
		{
			currentState = JUMP_UP;
			currentAnimation = &jumpUp;
			position.y -= 2;
		}
		break;
	
	case JUMP_MID_AIR:
		currentState = JUMP_DOWN;
		currentAnimation = &jumpDown;
		break;

	case JUMP_DOWN:
		if(jumpDown.isLastFrame)
		{
			currentState = IDLE;
			currentAnimation = &idle;
		}
		else
		{
			currentState = JUMP_DOWN;
			currentAnimation = &jumpDown;
			position.y += 2;
		}
		break;
	default:
		break;
	}
	
	if (position.x < minPosition)
		position.x = minPosition;
	else if (position.x > maxPosition)
		position.x = maxPosition;


	//printf("pos.x: %d", position.x);
	//assert(currentAnimation == nullptr);
	App->renderer->Blit(graphics, position.x, position.y, &currentAnimation->GetCurrentFrame(), 1.75f);
	// make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)

	return UPDATE_CONTINUE;
}