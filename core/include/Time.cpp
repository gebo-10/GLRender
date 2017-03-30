#include <Time.h>
Timer::Timer()
{
}

Timer::~Timer()
{
}

Uint32 Timer::GetTick()
{
	return SDL_GetTicks();
}