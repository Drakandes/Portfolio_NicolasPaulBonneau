#include "stdafx.h"
#include "Deltatime.h"

Deltatime::Deltatime()
{
}

Deltatime::~Deltatime()
{
}

float Deltatime::GetDeltaTime()
{
	current_time = clock_deltatime.getElapsedTime().asSeconds();
	float DELTATIME = current_time - last_time;
	last_time = current_time;
	return DELTATIME;
}
