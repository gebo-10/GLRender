#ifndef _TIMER_HPP
#define _TIMER_HPP
#pragma once
#include <Base.hpp>
#include <SDL/SDL.h>
class Timer
{
public:
	Timer();
	~Timer();
	Uint32 GetTick();
private:

};

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

#endif