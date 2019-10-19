#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "assert.h"
#include "ModuleSceneHonda.h"
#include "SDL/include/SDL.h"


ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : Module(start_enabled)
{
	//assert(true);

	//ground
	ground.x = 7;
	ground.y = 375;
	ground.w = 849;
	ground.h = 65;

	//background
	background.x = 120;
	background.y = 128;
	background.w = 671;
	background.h = 199;

	//ceilling
	ceilling.x = 91;
	ceilling.y = 8;
	ceilling.w = 765;
	ceilling.h = 48;

	//pool
	pool.x = 163;
	pool.y = 65;
	pool.w = 337;
	pool.h = 52;

	//water
	waterFromPool.speed = 0.025f;
	waterFromPool.frames.push_back({ 8,448,284,18 });
	waterFromPool.frames.push_back({ 296,448,284,12 });
	waterFromPool.frames.push_back({ 588,448,284,8 });


}


ModuleSceneHonda::~ModuleSceneHonda()
{
}

bool ModuleSceneHonda::Start()
{
	LOG("Loading honda scene");

	graphics = App->textures->Load("honda_stage2.png");

	App->player->Enable();
	// TODO 0: trigger background music
	App->audio->PlayMusic("honda.ogg");


	return true;
}

update_status ModuleSceneHonda::Update()
{
	App->renderer->Blit(graphics, 50, -15, &background, 1.75f); // background
	App->renderer->Blit(graphics, 0, 160, &ground, 1.75f); // ground
	App->renderer->Blit(graphics, 0, -15, &ceilling, 1.75f); // ceilling
	App->renderer->Blit(graphics, 230, 125, &pool, 1.75f); // pool
	App->renderer->Blit(graphics, 258, 137, &(waterFromPool.GetCurrentFrame()), 1.75f); // water animation

	if (App->input->GetKey(SDL_SCANCODE_SPACE))
	{
		App->fade->FadeToBlack((Module*)App->scene_ken, this, 3.0f);
		App->player->maxPosition = 720;
	}

	return UPDATE_CONTINUE;
}

bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading honda scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}
