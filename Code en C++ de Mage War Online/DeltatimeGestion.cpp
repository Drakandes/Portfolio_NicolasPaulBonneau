#include "stdafx.h"
#include "DeltatimeGestion.h"

DeltatimeGestion::DeltatimeGestion()
{
}

DeltatimeGestion::~DeltatimeGestion()
{
}

float DeltatimeGestion::GetDeltaTime()
{
	current_time = clock_deltatime.getElapsedTime().asSeconds();
	float DELTATIME =  current_time - last_time;
	last_time = current_time;
	return DELTATIME;
}
