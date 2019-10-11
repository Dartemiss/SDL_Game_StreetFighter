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
	position.y = 216;

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
		else
		{
			currentState = IDLE;
			currentAnimation = &idle;
		}
		break;
	default:
		break;
	}
	
	//printf("pos.x: %d", position.x);
	//assert(currentAnimation == nullptr);
	App->renderer->Blit(graphics, position.x, 125, &currentAnimation->GetCurrentFrame(), 1.75f);
	// make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)

	return UPDATE_CONTINUE;
}