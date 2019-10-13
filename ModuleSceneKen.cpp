#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKen.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneKen::ModuleSceneKen(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// TODO 2 : setup the foreground (red ship) with
	// coordinates x,y,w,h from ken_stage.png
	//Foreground (ship)
	foreground.x = 0;
	foreground.y = 0;
	foreground.w = 540;
	foreground.h = 202;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.frames.push_back({848, 208, 40, 40});
	flag.frames.push_back({848, 256, 40, 40});
	flag.frames.push_back({848, 304, 40, 40});
	flag.speed = 0.08f;

	// TODO 4: Setup Girl Animation from coordinates from ken_stage.png
	girlOfShip.speed = 0.07f;
	girlOfShip.frames.push_back({624,17,32,50});
	girlOfShip.frames.push_back({624,81,32,50});
	girlOfShip.frames.push_back({624,145,32,50});

	shipMovementSpeed = 0.05f;
	shipShiftMovement = -29.0f;
}

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");
	
	graphics = App->textures->Load("ken_stage.png");

	// TODO 7: Enable the player module
	App->player->Enable();
	// TODO 0: trigger background music
	App->audio->PlayMusic("ken.ogg");
	
	
	return true;
}

// UnLoad assets
bool ModuleSceneKen::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneKen::Update()
{
	// TODO 5: make sure the ship goes up and down
	if(updown)
		shipShiftMovement += shipMovementSpeed;
	else
		shipShiftMovement -= shipMovementSpeed;

	if (shipShiftMovement < -29.0f)
		updown = true;
	else if (shipShiftMovement > -25.0f)
		updown = false;

	// Draw everything --------------------------------------
	// TODO 1: Tweak the movement speed of the sea&sky + flag to your taste
	App->renderer->Blit(graphics, 0, 0, &background, 1.75f); // sea and sky
	App->renderer->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 1.75f); // flag animation

	// TODO 3: Draw the ship. Be sure to tweak the speed.
	App->renderer->Blit(graphics, -7, (int)shipShiftMovement, &foreground, 1.75f); // sea and sky
	//TODO 6: Draw the girl. Make sure it follows the ship movement!
	App->renderer->Blit(graphics, 193, (int)shipShiftMovement + 128, &(girlOfShip.GetCurrentFrame()), 1.75f); // flag animation
	App->renderer->Blit(graphics, 0, 170, &ground);

	// TODO 10: Build an entire new scene "honda", you can find its
	// and music in the Game/ folder

	// TODO 11: Make that pressing space triggers a switch to honda logic module
	// using FadeToBlack module
	if(App->input->GetKey(SDL_SCANCODE_SPACE))
	{
		//App->fade->FadeToBlack(App->scene_honda, this, 3.0f);
	}

	return UPDATE_CONTINUE;
}