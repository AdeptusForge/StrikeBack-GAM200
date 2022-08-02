#include "TimeKeeping.h"
#include "SDL_timer.h"
#include "Input.h"
#include "Events.h"
#include "glfw3.h"


#define FIXED_UPDATE_RATE 120

//Shows number of ticks since last update, useful for running time-based functions.
Uint64 deltaTime;
Uint64 startup;
Uint64 totalTicksSinceStartup;
float physicsFrameInTicks;
Uint64 currTick;
Uint64 priorTick;
bool lastFrameRender;
int totalRenders = 0;

std::vector<Event_Timer> allTimers;

//Gets the current ticks per frame. Used mostly in timestep testing.
int GetCurrentTick()
{
	return (int)(currTick / physicsFrameInTicks);
};

//Begins time startup.
void TimeStartup()
{
	startup = SDL_GetPerformanceCounter();
	physicsFrameInTicks = (float)(SDL_GetPerformanceFrequency() / (float)FIXED_UPDATE_RATE);
	priorTick = startup;
	//WriteDebug(to_string(physicsFrameInTicks));
};

void FixedUpdate(GLFWwindow* window)
{
	priorTick = currTick;
	for (int i = 0; i < allTimers.size(); i++)
	{
		allTimers[i].TimerUpdate();
	}
	SaveInputs(window);

	
	//PhysicsUpdate();
	EventManagerUpdate();
}

void VariableUpdate(GLFWwindow* window) 
{
	//RenderUpdate(window);
	RunInputs();
	//UpdateMap();
}


//Updates game time based on the computer's clock and the current tick. 
//Updates Rendering, Physics, Inputs, and map interactions.
void UpdateTime(GLFWwindow* window)
{
	currTick = SDL_GetPerformanceCounter();
	deltaTime = currTick - priorTick;
	if (deltaTime >= physicsFrameInTicks)
		FixedUpdate(window);

	VariableUpdate(window);
}