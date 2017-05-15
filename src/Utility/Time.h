#ifndef _TIMER_H
#define _TIMER_H
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


#endif