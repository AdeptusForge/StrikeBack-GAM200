#pragma once
#include "MADRengine/MADRpch.h"
#include "SDL.h"
#include "Events.h"

class Collider: public EventListener
{
private:

public:

	void EventResponse(EVENT e) 
	{
		InputFrame i = e.data.GetInputs();
		if (i.BUTTON_1())
		{

		}
	}
};