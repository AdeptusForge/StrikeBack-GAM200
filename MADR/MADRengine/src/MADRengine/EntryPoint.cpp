#include "MADRengine/MADRpch.h"
#include "EntryPoint.h"
#include "Input.h"
#include "Collision.h"
#include "Render.h"

Collider c;
GLFWwindow** window;

bool EngineStartup()
{
	EventStartup();
	window = RenderStartup();
	InputControlStartup(window);
	c.typeCriterion.push_back(EventType::Input_Event);
	AddEventListener(&c);
	return true;
}

bool EngineRunning() 
{
	return true;
}
void CentralLoop() 
{
	if(EngineStartup())
		while (EngineRunning())
		{
			UpdateTime(*window);
			RenderUpdate(*window);
		}
}