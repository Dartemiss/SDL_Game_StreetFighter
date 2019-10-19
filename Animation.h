#pragma once
#include <vector>

using namespace std;

class Animation
{
public:
	float speed;
	vector<SDL_Rect> frames;
	bool isLastFrame = false;

private:
	float current_frame;
	
public:
	Animation() : frames(), speed(1.0f), current_frame(0.0f)
	{}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		isLastFrame = current_frame >= frames.size() ? true : false;
		if(current_frame >= frames.size())
			current_frame = 0.0f;

		
		return frames[(int)current_frame];
	}
};