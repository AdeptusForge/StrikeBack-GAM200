#include "MADRengine/MADRpch.h"
#include "EntryPoint.h"
#include "Input.h"
#include "Collision.h"
#include "Render.h"

Collider c;
GLFWwindow** window;
/*! \mainpage MADR Engine Documentation
 *
 * \section intro_sec Introduction
 *
 * developed by Steffen Simmons with support from Nico Toe
 * 
 * MADR engine is a game engine intended both to work as a test production for team Fuzzy Guard and for use in later projects.
 *
 * \section Design Goals




<span style="text-decoration:underline;">Design Goals</span>



* * Build an engine that can handle any feasible game testing that I'd like to do for the foreseeable future with minimal coding (outside of ).
* * Build an engine robust enough to ship projects on into the future if need-be
* * Have a fast and quickly accessible UI
* * Be quick to construct(1 year time frame)
* * Be quick to debug and assess

Required Features



1. OpenGL functionality
2. Subframe input detection
3. Input Macro Detection
4. Fixed & Variable Frame Rates
5. Predictive Game Simulation
6. Event System
7. JSON Integration
8. Camera Control Modifiability

Desired Features



9. Active asset reloading
10. Hot Code Reloading
11. Function Reflection
12. Modifiable Physics & Collision System
13. Multi-thread Processing
14. Compute Shaders

<span style="text-decoration:underline;">Debugging</span>

Past debugging has been particularly troubling, as oftentimes I am fumbling around with black boxes trying to find what is wrong with the program and looking up. This leads to cobbling solutions together or creating hacky workarounds instead of actually understanding the problem in question. 

The solutions to this are many, but can be addressed during engine creation rather than midway through like with the MAADengine. 



 Increased use of Namespaces
Reduced use of pointers
Increased exception handling along every step of any given process
* * Automated testing cases
* * No Just-Right testing; make tests that try to cause errors as much as possible, in ways you wouldn't anticipate

Error Levels



* * Halting - an error that would immediately cause the game to crash or become non-functional
    * * Infinite Loop
    * *Input Detection Breaking
    * *
* * Asset Issues
    * * No File Found
    * * No Data Found
    * * Incorrect Data (asset verification?)
* * Unhandled Case(unknown error)
* * Event Issue
    * * Mistimed Event
    * * Missing Event Data
    * * Incorrect Event Data?

<span style="text-decoration:underline;">Game & Engine Separation</span>

To keep the engine disintegrated from the rest of the game, both the game and the engine are separate projects. The interactions between these two is also limited to prevent errors and to make sure that the engine and game logic can be decoupled.

Engine Responsibilities



* * Input Detection
* * Data Tracking & Logging
* * Event Handling
* * Exceptions
* * Rendering Pipeline & General Shaders
* * ECS
* * Editing UI
* * UI Framework
* * World Simulation

Game Responsibilities



* * Physics
* * Game Logic
* * Data Tracking & Logging
* * API linking (Steam, GOG, etc.)
* * Multiplayer
* * Specific Shaders
* * Editing UI
* * Game UI
* * Input Reaction

<span style="text-decoration:underline;">Engine RunTimeLine</span>


<table>
  <tr>
   <td>Start Events
   </td>
   <td>Physics Update 1
   </td>
   <td>Physics Update 2
   </td>
   <td>Post Physics Events
   </td>
   <td>PreDraw
<p>
Update
   </td>
   <td>Drawing to screen
   </td>
   <td>PostDrawUpdate
   </td>
   <td>End Events
   </td>
  </tr>
</table>


Start Events


    Input Reaction


        Activates any requisite actions that occur because of inputs in the game. Run in the Game segment and filtered over to the engine segment as needed. Examines data from the last several frames as well.


    Input Polling


        Checks for input changes, stores the last state of the input system as well as the current input changes.


    Physics Update(s)


    	Occurs before any draw events, and simulates physics not only for the current frame, but also the next several frames for interpolation purposes. 


    Post Physics Events


    	Input Polling


    PreDrawUpdate


        Render Prep


        Getting objects ready to be rendered, such as getting their final positions from any world simulation/physics system.

	Camera Changes

		Anything that might change the camera frustrum goes here.

	Animation Changes & Events

		Anything concerned with animation transitions

	Timer Updates

	Game Logic Changes

	Draw

		Rendering

	PostDrawUpdate

		Render Cleanup

			Clearing memory of unnecessary and unused data.

		Next Frame Game Logic Changes

	End Events

	Input Polling


 */

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